#include "ServerSocket.hpp"
#include "Utilities.hpp"
namespace NETWORK{

    bool ServerSocket::bind(const std::string&ip,  uint16_t portNumber)noexcept
    {
        if(!isValidPortNumber(portNumber))
        {
            return false;
        }
        // bind the socket
        sockaddr_in serverAddr;
        serverAddr.sin_port = htons(portNumber);
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
        std::cout << this->m_socketfd << "\n";
        return !IS_FAILED_SYSCALL(::bind(m_socketfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)));
    }
    bool ServerSocket::isConnected(void)const noexcept
    {
        return m_isConnectedServer;
    }
    bool ServerSocket::isValidPortNumber(uint16_t portNumber) const noexcept
    {
        if((portNumber < MIN_PORT_VALUE) || (portNumber > MAX_PORT_VALUE))
        {
            return false;
        }
        return true;
    }
    ServerSocket::ServerSocket(uint16_t portNumber, const std::string &ip):m_address{ip}, m_port{portNumber}, m_client{INVALID_SOCKET}, m_socketfd{INVALID_SOCKET}
    {
    }
    bool ServerSocket::CreateSocket() noexcept
    {
        //Create a socket
        // check if the m_socketfd is not created before
        if(this->m_socketfd == -1)
        {
            this->m_socketfd = socket(AF_INET, SOCK_STREAM, 0);
            if(this->m_socketfd == INVALID_SOCKET)
            {
                ERROR("socket failed");
            }
        }
        return !IS_FAILED_SYSCALL(this->m_socketfd);
    }
    bool ServerSocket::connect() noexcept
    {
        // bind the socket
        if(this->bind(m_address, m_port)) 
        {
            ERROR("Bind Excuted ");
            //start listen
            if(!IS_FAILED_SYSCALL(::listen(this->m_socketfd, m_numberOfClients)))
            {
                m_isConnectedServer = true;
                return true;
            }
        }
        ERROR("El72onaaaa     Bind failed");
        return false;      
    }
    bool ServerSocket::send(const std::string &message) noexcept
    {
        return !IS_FAILED_SYSCALL(::write(m_socketfd, &message, message.length()));
    }
    bool ServerSocket::read(std::string &buffer, uint16_t bufferSize) noexcept
    {
        return !IS_FAILED_SYSCALL(::read(m_socketfd, &buffer, bufferSize));
    }
    SOCKET ServerSocket::get_client_socket(void)const noexcept
    {
        return m_client;
    }
    void ServerSocket::close_client_socket(void)noexcept
    {
        if(!IS_INVALID_SOCKET(m_client))
        {
            ::close(m_client);
            m_client = INVALID_SOCKET;
        }
    }
    bool ServerSocket::accept(void) noexcept
    {
        struct sockaddr_in l_clientAdd;
        socklen_t l_clientAddLen = sizeof(l_clientAdd);
        m_client = ::accept(m_socketfd, (struct sockaddr*)&l_clientAdd, &l_clientAddLen);
        return !IS_INVALID_SOCKET(m_client);
    }
    bool ServerSocket::listen(void) noexcept
    {
        //start listen
        return !IS_FAILED_SYSCALL(::listen(m_socketfd, m_numberOfClients));
    }
    ServerSocket::~ServerSocket() noexcept
    {
        if(!IS_INVALID_SOCKET(m_socketfd))
        {
            ::close(m_socketfd);
            m_socketfd = INVALID_SOCKET;
        }
        if(!IS_INVALID_SOCKET(m_client))
        {
            ::close(m_client);
            m_client = INVALID_SOCKET;
        }
    }

}