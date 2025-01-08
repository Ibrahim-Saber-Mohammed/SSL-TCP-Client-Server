#ifndef _SESSION_MANGER__HPP
#define _SESSION_MANGER__HPP

#include <memory>
#include <functional>
#include <mutex>
#include <thread>
#include "ISocket.hpp"
#include "ServerSocket.hpp"
#include "Utilities.hpp"
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "ThreadSafetyQueue.hpp"
#include "EventLoop.hpp"

namespace NETWORK{

    class SessionManager : public std::enable_shared_from_this<SessionManger> {
        public:
        using OnRecieved = std::function<void(std::unique_ptr<std::string>)>;
        using OnAccept = std::function<void(void)>;
        using MutexGuard = std::lock_guard<std::mutex>;
        SessionManager(std::shared_ptr<IServerSocket>socket, SSL_CTX* ctx);
        void start(void);
        ~SessionManager();
        SessionManager(const SessionManager&) = delete;
        SessionManager& operator = (const SessionManager& ) = delete;
        SessionManager(SessionManager&&) = delete;
        SessionManager& operator(SessionManager&&) = delete;
        private:
            void do_HandShake(void);
            void do_read(void);
            bool do_write();
            void processQueue(void);
            OnRecieved onRecievedCallBack;
            char m_buffer[1024];
            SSL* m_ssl{nullptr};
            std::shared_ptr<IServerSocket> m_socket;
            std::shared_ptr<EventLoop> m_eventLoop{nullptr};
            SOCKET m_client{INVALID_SOCKET};
    };
}

#endif