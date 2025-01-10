#include <Server/Server.hpp>

namespace NETWORK
{
    Server::Server(std::unique_ptr<IServerSocket> ServerStartegy):m_Server{std::move(ServerStartegy)}
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
        m_eventloop->attachCallBack(m_Server->git_server_socket(),
                                     EventLoop::ActionType::RECIEVE, 
                                     [this](){this->do_accept();});
        m_eventloop->run();
        
    }
    void Server::do_accept(void)
    {
        if (m_Server->accept())
        {
            std::shared_ptr<SessionManager> session = std::shared_ptr<SessionManager>(new SessionManager(m_Server, m_eventloop));
            m_sessions.push_back(session);
            session->start();
        }
    }
}