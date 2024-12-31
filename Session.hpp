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

    class SessionManger : public std::enable_shared_from_this<SessionManger> {
        public:
        using OnRecieved = std::function<void(std::unique_ptr<std::string>)>;
        using OnAccept = std::function<void(void)>;
        using MutexGuard = std::lock_guard<std::mutex>;
        SessionManger(std::shared_ptr<IServerSocket>socket, SSL_CTX* ctx);
        void start(void);
        ~SessionManger();
        

    private:
        void do_HandShake(void);
        void do_read(void);
        bool do_write();
        void processQueue(void);
        bool isDataReady(void);
        void stopProcessing(void);
        std::mutex m_mtx;
        ThreadSafeQueue<std::unique_ptr<std::string>>m_queue;
        bool m_stopProcessing{false};
        std::thread m_processingThread;
        std::thread m_readThread;
        std::condition_variable m_cv;
        OnRecieved onRecievedCallBack;
        char m_buffer[1024];
        SSL* m_ssl{nullptr};
        std::shared_ptr<IServerSocket> m_socket;
        std::shared_ptr<EventLoop> m_eventLoop{nullptr}
    };
}

#endif