#ifndef _Server__HPP___
#define _Server__HPP___

#include <memory>
#include "ServerSocket.hpp"
#include "Session.hpp"
#include "EventLoop.hpp"

namespace NETWORK
{
    class Server
    {
    public:
        // types
        using OnRecieved = std::function<void(std::unique_ptr<std::string>)>;
        using OnAccept = std::function<void(void)>;
        Server(SSL_CTX*ctx,
                   std::unique_ptr<IServerSocket> ServerStartegy);
        ~Server() =  default;
        void run();

    private:
       void do_accept(void);
    // members
        std::mutex m_mtx;
        std::shared_ptr<IServerSocket> m_Server;
        std::vector<std::shared_ptr<SessionManger>> m_sessions;
        std::vector<SOCKET> m_clients;
        SSL_CTX* m_ctx; // to be fixed (strive to rule of Zero (not owning this object))
        std::shared_ptr<EventLoop> m_eventloop{nullptr};
    };
}

#endif