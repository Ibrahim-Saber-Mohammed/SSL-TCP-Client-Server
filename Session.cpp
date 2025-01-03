#include "Session.hpp"
#include <sys/select.h>

namespace NETWORK
{
    SessionManger::SessionManger(std::shared_ptr<IServerSocket> socket, SSL_CTX *ctx) : m_socket{socket}, m_ssl{SSL_new(ctx)}
    {
        m_client = m_socket->get_client_socket();
        SSL_set_fd(m_ssl, m_client);
        // Check if SSL was created successfully
        if (!m_ssl)
        {
            // Handle SSL initialization error
            throw std::runtime_error("Failed to create SSL object");
        }
    }

    void SessionManger::start(void)
    {
        // Create a new thread for each session
        SSL_set_fd(m_ssl, m_client);
        std::cout << "Handshake thread created\n";
        m_eventLoop->attachCallBack(m_client, EventLoop::ActionType::RECIEVE, [this]()
                                    { this->do_HandShake(); });
        // to be fixed an integrate a thread pool pattern instead
        m_processingThread = std::thread(&SessionManger::processQueue, shared_from_this());
    }
    SessionManger::~SessionManger()
    {
        stopProcessing();
        if (m_ssl)
        {
            SSL_free(m_ssl);
        }
    }
    void SessionManger::stopProcessing(void)
    {
        MutexGuard lock(m_mtx);
        m_stopProcessing = true; // Set the stop flag
        m_cv.notify_all();       // Notify any waiting threads
        if (m_processingThread.joinable())
        {
            m_processingThread.join(); // Wait for the processing thread to finish
        }
        if (m_readThread.joinable())
        {
            m_readThread.join(); // Wait for the read thread to finish
        }
    }
    void SessionManger::do_HandShake(void)
    {
        std::unique_lock<decltype(m_mtx)> lock(m_mtx);
        std::cout << "Server HandShaken starts\n";
        if ((SSL_accept(m_ssl) <= 0))
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
            std::cout << "Data Ready to be readn";
            m_readThread = std::thread(&SessionManger::do_read, shared_from_this());
            m_readThread.detach();
            std::cout << "do read thread created\n";
        }
    }
    void SessionManger::do_read(void)
    {
        const auto l_valRecieved = SSL_read(m_ssl, &m_buffer, sizeof(m_buffer));
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
        m_cv.notify_all(); // Notify the processing thread
        std::cout << "do read thread ends\n";
    }

    void SessionManger::processQueue(void)
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