#include <SessionManager/Session.hpp>
#include <sys/select.h>

namespace NETWORK
{
    SessionManager::SessionManager(std::shared_ptr<IServerSocket> socket, std::shared_ptr<EventLoop>eventloop, 
                                    std::shared_ptr<ThreadPool>_threadPool) : m_socket{socket}, m_eventLoop{eventloop}, m_threadPool{_threadPool}
    {
        m_ssl_wrapper = std::make_shared<SSL_Wrapper>(socket->get_client_socket());
        m_client = m_socket->get_client_socket();
    }
    void SessionManager::start(void)
    {
        try {
            if(m_ssl_wrapper)
            {
                m_eventLoop->attachCallBack(m_ssl_wrapper->get_fd(),
                                        EventLoop::ActionType::RECIEVE,
                                        [this](){ this->do_HandShake(); });
            }
        }
        catch (const std::exception& e) {
        // Handle exception
        std::cerr << "Exception caught: " << e.what() << std::endl;
        // Release resources
        m_eventLoop->detachCallBack(m_ssl_wrapper->get_fd(), EventLoop::ActionType::RECIEVE);
        m_socket->close_client_socket();
        m_ssl_wrapper.reset();
        m_client = INVALID_SOCKET;
        }
    }
    SessionManager::~SessionManager()
    {
        m_eventLoop->detachCallBack(m_ssl_wrapper->get_fd(), EventLoop::ActionType::RECIEVE);
        m_eventLoop->detachCallBack(m_ssl_wrapper->get_fd(), EventLoop::ActionType::WRITE);
        m_socket->close_client_socket();  
        m_client = INVALID_SOCKET;
        m_ssl_wrapper.reset();
    }
    void SessionManager::do_HandShake(void)
    {
        if ((m_ssl_wrapper->do_handshake() <= 0))
        {
            // Handle SSL handshake error
            ERR_print_errors_fp(stderr);
            m_eventLoop->detachCallBack(m_ssl_wrapper->get_fd(),
                                    EventLoop::ActionType::RECIEVE);
            m_socket->close_client_socket();
            m_ssl_wrapper.reset();
            m_client = INVALID_SOCKET;
            ERROR("INVALID SECURITY .... ")
        }
        else
        {
            // Process the data
            m_eventLoop->attachCallBack(m_ssl_wrapper->get_fd(), EventLoop::ActionType::WRITE,
                                         [this](){ this->enqueueWriteTask(); });
        }
    }
    void SessionManager::enqueueWriteTask(void)
    {
        m_threadPool->enqueue([this](){this->do_write();});
    }
    void SessionManager::enqueueReadTask(void)
    {
        m_threadPool->enqueue([this](){this->do_read();});
    }
    void SessionManager::do_read(void)
    {
        std::unique_lock<std::mutex> lock(m_socketMutex);
        m_writeCond.wait(lock, [this]{ return m_writeComplete; });
        const auto l_valRecieved = m_ssl_wrapper->receive(m_buffer, sizeof(m_buffer));
        if (l_valRecieved <= 0)
        {
            std::cout << "Client disconnected, ip:\n";
            ERROR("Couldn't read from the client");
            m_eventLoop->detachCallBack(m_client, EventLoop::ActionType::RECIEVE);
            m_socket->close_client_socket();
        }
        else
        {
            m_buffer[l_valRecieved] = '\0';
            std::cout << "Data received from client: " << m_buffer << "n";
            
        }
        m_writeComplete = false;
    }
    void SessionManager::do_write(void)
    {
        std::lock_guard<std::mutex> lock(m_socketMutex);
        // if ()
        // {
            
        // }
        // else
        // {
            
        //     m_eventLoop->attachCallBack(m_ssl_wrapper->get_fd(), EventLoop::ActionType::RECIEVE, 
        //                                 [this](){ this->enqueueReadTask(); });
        // }
        m_writeComplete = true;
        m_writeCond.notify_all();

    }
}