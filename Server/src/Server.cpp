#include <Server/Server.hpp>

namespace NETWORK
{
    Server::Server(std::unique_ptr<IServerSocket> ServerStartegy,
                    std::shared_ptr <ThreadPool> _threadPool,
                    std::shared_ptr <EventLoop>_eventLoop):m_Server(std::move(ServerStartegy)), m_eventloop(_eventLoop), m_threadPool(_threadPool)
    {
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
            std::shared_ptr<SessionManager> session = std::shared_ptr<SessionManager>(new SessionManager(m_Server, m_eventloop, m_threadPool));
            m_threadPool.enqueue( [session](){ session->start();});
        }
    }
}