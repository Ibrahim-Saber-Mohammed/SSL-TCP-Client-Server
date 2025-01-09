#include "Session.hpp"
#include <sys/select.h>

namespace NETWORK
{
    SessionManager::SessionManager(std::shared_ptr<IServerSocket> socket) : m_socket{socket},
                                  m_ssl_wrapper{std::make_shared<SSL_Wrapper>(socket->get_client_socket())}
    {
        m_client = m_socket->get_client_socket();
    }
    void SessionManager::start(void)
    {
        SSL_set_fd(m_ssl, m_client);
        std::cout << "Handshake thread created\n";
        m_eventLoop->attachCallBack(m_ssl_wrapper->get_fd(), EventLoop::ActionType::RECIEVE, [this]()
                                    { this->do_HandShake(); });
        // to be fixed an integrate a thread pool pattern instead
        m_processingThread = std::thread(&SessionManager::processQueue, shared_from_this());
    }
    SessionManager::~SessionManager()
    {
        stopProcessing();
        if (m_ssl)
        {
            SSL_free(m_ssl);
        }
    }
    void SessionManager::do_HandShake(void)
    {
        std::unique_lock<decltype(m_mtx)> lock(m_mtx);
        std::cout << "Server HandShaken starts\n";
        if ((m_ssl_wrapper->do_handshake() <= 0))
        {
            // Handle SSL handshake error
            ERR_print_errors_fp(stderr);
            SSL_free(m_ssl);
            m_ssl = nullptr;
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
        }
    }
    void SessionManager::do_read(void)
    {
        const auto l_valRecieved = m_ssl_wrapper->receive( &m_buffer, sizeof(m_buffer));
        std::cout << " do read thread Started\n";
        if (l_valRecieved <= 0)
        {
            std::cout << "Client disconnected, ip:\n";
            ERROR("Couldn't read from the client");
            SSL_shutdown(m_ssl);
            SSL_free(m_ssl);
            m_ssl = nullptr;
            m_eventLoop->detachCallBack(m_client, EventLoop::ActionType::RECIEVE);
            m_socket->close_client_socket();
            m_stopProcessing = true;
        }
        else
        {
            m_buffer[l_valRecieved] = '\0';
            std::cout << "Data received from client: " << m_buffer << "n";
            std::unique_ptr<std::string> data(new std::string(m_buffer));
            m_queue.push(std::move(data));
            std::cout << "Data Pushed to the queue\n";
        }
        std::cout << "do read thread ends\n";
    }
    void SessionManager::processQueue(void)
    {
        std::cout << "Processing thread Starts\n";
        while (!m_stopProcessing)
        {
            std::unique_ptr<std::string> data;
            std::unique_lock<decltype(m_mtx)> lock(m_mtx);
            m_cv.wait(lock, [this]
                      { return !m_queue.empty() || m_stopProcessing; }); // Wait for data or stop signal
            if (m_stopProcessing)
            {
                break;
            } // Exit if stopping
            std::cout << "Thread notified..\n";
            if (!m_queue.empty())
            {
                std::cout << "Queue not empty..\n";
                if (m_queue.pop(data))
                {
                    std::string message = data->c_str();
                    std::cout << "Received message: " << message << "\n";
                    // onRecievedCallBack(std::move(data));
                }
            }
        }
    }
}