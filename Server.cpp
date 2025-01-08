#include "Server.hpp"

namespace NETWORK
{
    Server::Server(SSL_CTX *ctx,std::unique_ptr<IServerSocket> ServerStartegy) :m_Server{ServerStartegy}, m_ctx{ctx}
    {
        m_eventloop = std::shared_ptr<EventLoop>(new EventLoop(m_Server->git_server_socket()));
        if (!m_Server->CreateSocket())
        {
            ERROR("Failedto create the Socket");
        }
    }
    void Server::run()
    {
        if (!m_Server->isConnected())
        {
            m_Server->connect();
        }
        m_eventloop->attachCallBack(m_Server->git_server_socket(), EventLoop::ActionType::RECIEVE, [this](void){this->do_accept();});
        m_eventloop->run();
        
    }
    void Server::do_accept(void)
    {
        if (m_Server->accept())
        {
            std::cout << "Client connected..." << std::endl;
            std::lock_guard<decltype(m_mtx)> lock(m_mtx);
            std::shared_ptr<SessionManger> session = std::shared_ptr<SessionManger>(new SessionManager(m_Server, m_ctx));
            m_sessions.push_back(session);
            std::cout << "SessionCreated \n";
            session->start();
        }
    }
}