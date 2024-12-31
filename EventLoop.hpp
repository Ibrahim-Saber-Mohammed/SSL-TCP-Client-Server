#ifndef _EVENTLOOP__HPP__
#define _EVENTLOOP__HPP__

#include <memory>
#include <functional>
#include <mutex>
#include <unordered_map>
#include "Utilities.hpp"

namespace NETWORK{

    class EventLoop{
        enum class ActionType{
            RECIEVE, WRITE, BOTH
        };
        public:
        EventLoop();
        using OnActionCallBack= std::function<void(void)>;
        using MutexGuard = std::lock_guard<std::mutex>;
        void run(void);
        void attachCallBack(SOCKET socketFd, ActionType type, OnActionCallBack callBack);
        void detachCallBack(SOCKET socketFd, ActionType type);
        private:
        std::unordered_map<SOCKET, OnActionCallBack>OnRecieveCallBack_map;
        std::unordered_map<SOCKET, OnActionCallBack>OnWriteCallBack_map;
        std::mutex m_mtx;
        fd_set m_masterSet;
        fd_set m_readSet;
        fd_set m_writeSet;
        size_t m_maxSocketFd;
    };

}
#endif