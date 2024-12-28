#ifndef SERVER_SOCKET__HPP__
#define SERVER_SOCKET__HPP__

#include "ISocket.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <openssl/opensslconf.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "Utilities.hpp"

namespace NETWORK
{
    constexpr uint8_t m_numberOfClients{10U};
    class ServerSocket : public IServerSocket
    {
    public:
        ServerSocket(uint16_t portNumber, const std::string& ip);
        virtual bool CreateSocket(void) noexcept override;
        virtual bool connect() noexcept override;
        virtual bool send(const std::string &message) noexcept override;
        virtual bool read(std::string &buffer, uint16_t bufferSize) noexcept override;
        virtual bool accept(void)noexcept override;
        virtual bool listen(void) noexcept override;
        virtual SOCKET get_client_socket(void)const noexcept override;
        virtual void close_client_socket(void) noexcept override;
        virtual ~ServerSocket()noexcept;
        virtual bool bind(const std::string& ip, uint16_t portNumber)noexcept override;
        virtual bool isConnected(void) const noexcept override;
        
    private:
        bool m_isConnectedServer{false};
        bool isValidPortNumber(uint16_t portNumber)const noexcept;
        SOCKET m_socketfd{-1};
        uint16_t m_port;
        std::string m_address;
        SOCKET m_client{-1};
    };
}

#endif