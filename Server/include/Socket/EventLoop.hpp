#ifndef _EVENTLOOP__HPP__
#define _EVENTLOOP__HPP__

#include <memory>
#include <functional>
#include <mutex>
#include <unordered_map>
#include <Server/Utilities.hpp>

namespace NETWORK{

    class EventLoop{
        public:
        enum class ActionType{
            RECIEVE, WRITE, BOTH
        };
        EventLoop();
        void setListenSocket(SOCKET listenSocket);
        using OnActionCallBack = std::function<void(void)>;
        using MutexGuard = std::lock_guard<std::mutex>;
        void run(void);
        void attachCallBack(SOCKET socketFd, ActionType type, OnActionCallBack callBack);
        void detachCallBack(SOCKET socketFd, ActionType type);
        private:
        std::unordered_map<SOCKET, std::tuple <OnActionCallBack, OnActionCallBack>>m_callBacks;
        std::mutex m_mtx;
        fd_set m_readSet;
        fd_set m_writeSet;
        SOCKET m_maxSocketFd;
        SOCKET m_listeneSocket{INVALID_SOCKET};
    };

}
#endif