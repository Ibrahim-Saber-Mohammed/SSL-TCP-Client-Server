#include "EventLoop.hpp"

namespace NETWORK
{
    EventLoop::EventLoop(SOCKET listenSocket) : m_maxSocketFd{0}, m_listeneSocket{listenSocket}
    {
        FD_ZERO(&m_masterSet);
        FD_ZERO(&m_readSet);
        FD_ZERO(&m_writeSet);
        FD_SET(m_listeneSocket, &m_masterSet);
        m_maxSocketFd = m_listeneSocket;
    }

    void EventLoop::run(void)
    {
        FD_ZERO(&m_readSet);
        FD_ZERO(&m_writeSet);
        while (true)
        {
            {
                MutexGuard lock(m_mtx);
                m_readSet = m_masterSet;
                m_writeSet = m_masterSet;
            }

            auto activity = select(m_maxSocketFd + 1, &m_readSet, &m_writeSet, nullptr, nullptr);
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
                if (FD_ISSET(m_listeneSocket, &m_readSet)) // handling server new connections
                {
                    //
                    std::unique_lock<std::mutex> lck(m_mtx);
                    auto callBack = OnRecieveCallBack_map.at(m_listeneSocket);
                    lck.unlock();
                    callBack();
                }
                for (auto iter{0}; iter < m_maxSocketFd; iter++)
                {
                    if (iter == m_listeneSocket)
                        continue;                        // handling server new connections
                    else if (FD_ISSET(iter, &m_readSet)) // handling other clients recieve data
                    {
                        std::unique_lock<std::mutex> lck(m_mtx);
                        auto callBack = OnRecieveCallBack_map.at(iter);
                        lck.unlock();
                        callBack();
                    }
                    else if (FD_ISSET(iter, &m_writeSet)) // handling write socekts
                    {
                        std::unique_lock<std::mutex> lck(m_mtx);
                        auto callBack = OnWriteCallBack_map.at(iter);
                        lck.unlock();
                        callBack();
                    }
                }
            }
        }
    }
    void EventLoop::attachCallBack(SOCKET socketFd, ActionType type, OnActionCallBack callBack)
    {
        MutexGuard lock(m_mtx);
        FD_SET(socketFd, &m_masterSet);
        if (socketFd > m_maxSocketFd)
        {
            m_maxSocketFd = socketFd;
        }
        if (type == ActionType::RECIEVE)
        {
            OnRecieveCallBack_map.insert({socketFd, callBack});
        }
        else if (type == ActionType::WRITE)
        {
            OnWriteCallBack_map.insert({socketFd, callBack});
        }
        else
        {
            OnRecieveCallBack_map.insert({socketFd, callBack});
            OnWriteCallBack_map.insert({socketFd, callBack});
        }
    }
    void EventLoop::detachCallBack(SOCKET socketFd, ActionType type)
    {
        MutexGuard lock(m_mtx);
        FD_CLR(socketFd, &m_masterSet);
        if (type == ActionType::RECIEVE)
        {
            OnRecieveCallBack_map.erase(socketFd);
        }
        else if (type == ActionType::WRITE)
        {
            OnWriteCallBack_map.erase(socketFd);
        }
        else
        {
            OnRecieveCallBack_map.erase(socketFd);
            OnWriteCallBack_map.erase(socketFd);
        }
        if (socketFd == m_maxSocketFd)
        {
            m_maxSocketFd = 0; // Reset to 0 and find the new maximum
            for (int i = 0; i < FD_SETSIZE; i++)
            {
                if (FD_ISSET(i, &m_masterSet) && i > m_maxSocketFd)
                {
                    m_maxSocketFd = i;
                }
            }
        }
    }
}