#ifndef _SESSION_MANGER__HPP
#define _SESSION_MANGER__HPP

#include <memory>
#include <functional>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <Socket/ISocket.hpp>
#include <Socket/ServerSocket.hpp>
#include <Server/Utilities.hpp>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <Server/ThreadPool.hpp>
#include <Socket/EventLoop.hpp>
#include <SessionManager/SSL_Wrapper.hpp>

namespace NETWORK{

    class SessionManager : public std::enable_shared_from_this<SessionManager> {
        public:
        using OnRecieved = std::function<void(std::unique_ptr<std::string>)>;
        using OnAccept = std::function<void(void)>;
        SessionManager(std::shared_ptr<IServerSocket>socket, std::shared_ptr<EventLoop>eventloop, 
                        std::shared_ptr<ThreadPool>_threadPool);
        void start(void);
        ~SessionManager();
        SessionManager(const SessionManager&) = delete;
        SessionManager& operator = (const SessionManager& ) = delete;
        SessionManager(SessionManager&&) = delete;
        SessionManager& operator=(SessionManager&&) = delete;
        private:
            void do_HandShake(void);
            void enqueueWriteTask(void);
            void enqueueReadTask(void);
            void do_read(void);
            void do_write(void);
            void processQueue(void);
            OnRecieved onRecievedCallBack;
            char m_buffer[1024];
            std::shared_ptr<IServerSocket> m_socket;
            std::shared_ptr<EventLoop> m_eventLoop{nullptr};
            std::shared_ptr<ThreadPool>m_threadPool;
            std::shared_ptr<SSL_Wrapper> m_ssl_wrapper;
            std::mutex m_socketMutex;
            std::condition_variable m_writeCond;
            bool m_writeComplete{false};
            SOCKET m_client{INVALID_SOCKET};
    };
}

#endif