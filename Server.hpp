#ifndef _TCP_SERVER__HPP___
#define _TCP_SERVER__HPP___

#include <memory>
#include "ServerSocket.hpp"
#include "Session.hpp"

namespace NETWORK
{
    class TCP_Server
    {
    public:
        // types
        using OnRecieved = std::function<void(std::unique_ptr<std::string>)>;
        using OnAccept = std::function<void(void)>;
        TCP_Server(SSL_CTX*ctx,
                   const std::string &ip,
                   uint16_t port);
        ~TCP_Server() =  default;
        void run();

    private:
       void do_accept(void);
    // members
        std::mutex m_mtx;
        std::shared_ptr<IServerSocket> m_Server;
        std::vector<std::shared_ptr<SessionManger>> m_sessions;
        std::vector<SOCKET> m_clients;
        SSL_CTX* m_ctx;
    };
}

#endif