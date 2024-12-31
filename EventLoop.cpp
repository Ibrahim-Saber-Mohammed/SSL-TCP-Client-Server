#include "EventLoop.hpp"

namespace NETWORK{
    EventLoop::EventLoop():m_maxSocketFd{0}
    {
        FD_ZERO(&m_masterSet);
        FD_ZERO(&m_readSet);
        FD_ZERO(&m_writeSet);
    }

    void EventLoop::run(void)
    {
        #if 0
        
        FD_ZERO(&readfd);
        while(true)
        {
            {
                MutexGuard lock(m_mtx);
                m_readSet = m_masterSet;
                m_writeSet = m_masterSet;
            }

            auto activity = select(m_maxSocketFd+1, &m_readSet, &m_writeSet, nullptr, nullptr);
            if (activity < 0)
            {
                // Handle error (e.g., log it)
                ERROR("Error the Select function did not excute successfully");
                return false;
            }
            else if (activity == 0)
            {
                // Handle timeout (e.g., log it)
                ERROR("Timeout the Select function did not excute successfully");
                return false;
            }
            for (auto iter{0}; iter<m_maxSocketFd; iter++)
            {
                if(ISSET()) // handling server new connections
                {

                }
                else if(ISSET()) // handling other clients recieve data
                {
                    MutexGuard lock(m_mtx);
                    auto callBack = OnRecieveCallBack_map.at();
                    callBack();
                }
                else if(ISSET()) // handling write socekts
                {
                    MutexGuard lock(m_mtx);
                    auto callBack = OnWriteCallBack_map.at();
                    callBack();
                }
            }
            
        }
        #endif
    }
    void EventLoop::attachCallBack(SOCKET socketFd, ActionType type, OnActionCallBack callBack)
    {
        MutexGuard lock(m_mtx);
        FD_SET(socketFd,&m_masterSet);
        if(type == ActionType::RECIEVE){
            OnRecieveCallBack_map.insert({socketFd, callBack});
        }
        else if(type == ActionType::WRITE){
            OnWriteCallBack_map.insert({socketFd, callBack});
        }
        else{
            OnRecieveCallBack_map.insert({socketFd, callBack});
            OnWriteCallBack_map.insert({socketFd, callBack});
        }
    }
    void EventLoop::detachCallBack(SOCKET socketFd, ActionType type)
    {
        MutexGuard lock(m_mtx);
        FD_CLR(socketFd, &m_masterSet);
        if(type == ActionType::RECIEVE){
            OnRecieveCallBack_map.erase(socketFd);
        }
        else if(type == ActionType::WRITE){
            OnWriteCallBack_map.erase(socketFd);
        }
        else{
            OnRecieveCallBack_map.erase(socketFd);
            OnWriteCallBack_map.erase(socketFd);
        }
    }
}