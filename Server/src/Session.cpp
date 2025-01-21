#include <SessionManager/Session.hpp>
#include <sys/select.h>

namespace NETWORK
{
    SessionManager::SessionManager(std::shared_ptr<IServerSocket> socket, std::shared_ptr<EventLoop>eventloop, 
                                    std::shared_ptr<ThreadPool>_threadPool) : m_socket{socket}, m_eventLoop{eventloop}, m_threadPool{_threadPool};
    {
        m_ssl_wrapper = std::make_shared<SSL_Wrapper>(socket->get_client_socket());
        m_client = m_socket->get_client_socket();
    }
    void SessionManager::start(void)
    {
        if(m_ssl_wrapper)
        {
            m_eventLoop->attachCallBack(m_ssl_wrapper->get_fd(),
                                    EventLoop::ActionType::RECIEVE,
                                    [this](){ this->do_HandShake(); });
        }
    }
    SessionManager::~SessionManager()
    {
    }
    void SessionManager::do_HandShake(void)
    {
        if ((m_ssl_wrapper->do_handshake() <= 0))
        {
            // Handle SSL handshake error
            ERR_print_errors_fp(stderr);

            m_socket->close_client_socket();
            ERROR("INVALID SECURITY .... ")
        }
        else
        {
            // Process the data
            //@TODO: Add the do read to the event loop class to monitor the sockets for data availabilty
            //@TODO: Implement thread pool to handle the multiple threads if needed to use multithreading
            m_eventLoop->attachCallBack(m_ssl_wrapper->get_fd(), EventLoop::ActionType::RECIEVE, [this]()
                                        { this->do_read(); });
            // m_eventLoop->attachCallBack(m_ssl_wrapper->get_fd(), EventLoop::ActionType::WRITE, [this]()
                                        // { this->do_write(); });
        }
    }
    void SessionManager::do_read(void)
    {
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
    }
    void SessionManager::processQueue(void)
    {
        std::cout << "Processing thread Starts\n";
        while (!true)
        {
            std::unique_ptr<std::string> data;
            std::cout << "Thread notified..\n";
            {
                std::cout << "Queue not empty..\n";

                std::string message = data->c_str();
                std::cout << "Received message: " << message << "\n";
                // onRecievedCallBack(std::move(data))
            }
        }
    }
}