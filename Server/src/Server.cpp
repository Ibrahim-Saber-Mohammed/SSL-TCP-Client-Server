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

        m_eventloop->setListenSocket(m_Server->git_server_socket());
        m_eventloop->run();
        
    }
    void Server::stop(void)
    {
        m_eventloop->close();
        m_threadPool->shutdown();
    }
    void Server::do_accept(void)
    {
        if (m_Server->accept())
        {
            auto session = std::make_shared<SessionManager>(m_Server, m_eventloop, m_threadPool);
            m_threadPool->enqueue( [session](){ session->start();});
        }
    }
}