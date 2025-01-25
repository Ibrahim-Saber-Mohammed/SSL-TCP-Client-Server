#include <Socket/EventLoop.hpp>
namespace NETWORK
{
    EventLoop::EventLoop() : m_maxSocketFd{0}
    {
        FD_ZERO(&m_readSet);
        FD_ZERO(&m_writeSet);
        
    }
    void EventLoop::setListenSocket(SOCKET listenSocket)
    {
        m_listeneSocket = listenSocket;
        FD_SET(m_listeneSocket, &m_readSet);
        m_maxSocketFd = m_listeneSocket;
    }
    void EventLoop::run(void)
    {
        fd_set tmp_read_fds, tmp_write_fds;
        FD_ZERO(&tmp_read_fds);
        FD_ZERO(&tmp_write_fds);
        while (true)
        {
            {
                MutexGuard lock(m_mtx);
                tmp_read_fds = m_readSet;
                tmp_write_fds = m_writeSet;
            }
            auto activity = select(m_maxSocketFd + 1, &tmp_read_fds, &tmp_write_fds, nullptr, nullptr);
            if (activity < 0)
            {
                // Handle error (e.g., log it)
                ERROR("Error the Select function did not excute successfully");
                // return false;
            }
            else if (activity == 0)
            {
                // Handle timeout (e.g., log it)
                ERROR("Timeout the Select function did not excute successfully");
                // return false;
            }
            else
            {
                if (FD_ISSET(m_listeneSocket, &tmp_read_fds)) // handling server new connections
                {
                    if (m_callBacks.count(m_listeneSocket) > 0 && std::get<0>(m_callBacks[m_listeneSocket]))
                    {
                        std::unique_lock<std::mutex> lck(m_mtx);
                        auto callBack = std::get<0>(m_callBacks[m_listeneSocket]);
                        lck.unlock();
                        callBack();
                    }
                }
                for (auto iter{0}; iter <= m_maxSocketFd; iter++)
                {
                    if (iter == m_listeneSocket)
                        continue;                           // handling server new connections
                    else if (FD_ISSET(iter, &tmp_read_fds)) // handling other clients recieve data
                    {
                        if (m_callBacks.count(iter) > 0 && std::get<0>(m_callBacks[iter]))
                        {
                            std::unique_lock<std::mutex> lck(m_mtx);
                            auto callBack = std::get<0>(m_callBacks[iter]);
                            lck.unlock();
                            callBack();
                        }
                    }
                    else if (FD_ISSET(iter, &tmp_write_fds)) // handling write socekts
                    {
                        if (m_callBacks.count(iter) > 0 && std::get<1>(m_callBacks[iter]))
                        {
                            std::unique_lock<std::mutex> lck(m_mtx);
                            auto callBack = std::get<1>(m_callBacks[iter]);
                            lck.unlock();
                            callBack();
                        }
                    }
                }
            }
        }
    }
    void EventLoop::attachCallBack(SOCKET socketFd, ActionType type, OnActionCallBack callBack)
    {
        if (socketFd > m_maxSocketFd)
        {
            m_maxSocketFd = socketFd;
        }
        if (type == ActionType::RECIEVE)
        {
            FD_SET(socketFd, &m_readSet);
            m_callBacks[socketFd] = std::make_tuple(callBack, std::get<1>(m_callBacks[socketFd]));
        }
        else if (type == ActionType::WRITE)
        {
            FD_SET(socketFd, &m_writeSet);
            m_callBacks[socketFd] = std::make_tuple(std::get<0>(m_callBacks[socketFd]), callBack);
        }
    }
    void EventLoop::detachCallBack(SOCKET socketFd, ActionType type)
    {
        MutexGuard lock(m_mtx);
        if (type == ActionType::RECIEVE)
        {
            FD_CLR(socketFd, &m_readSet);
            m_callBacks[socketFd] = std::make_tuple(nullptr, std::get<1>(m_callBacks[socketFd]));
        }
        else if (type == ActionType::WRITE)
        {
            FD_CLR(socketFd, &m_writeSet);
            m_callBacks[socketFd] = std::make_tuple(std::get<0>(m_callBacks[socketFd]), nullptr);
        }
        else
        {
            FD_CLR(socketFd, &m_readSet);
            FD_CLR(socketFd, &m_writeSet);
            m_callBacks[socketFd] = std::make_tuple(nullptr, nullptr);
        }
        if (std::get<0>(m_callBacks[socketFd]) == nullptr && std::get<1>(m_callBacks[socketFd]) == nullptr)
        {
            m_callBacks.erase(socketFd);
        }
        if (socketFd == m_maxSocketFd)
        {
            m_maxSocketFd = 0; // Reset to 0 and find the new maximum
            for (int i = 0; i < FD_SETSIZE; i++)
            {
                if (FD_ISSET(i, &m_readSet) || FD_ISSET(i, &m_writeSet))
                {
                    if (i > m_maxSocketFd)
                    {
                        m_maxSocketFd = i;
                    }
                }
            }
        }
    }
}