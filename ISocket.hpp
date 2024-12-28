#ifndef _ISOCKET__HPP__
#define _ISOCKET__HPP__

#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include "Utilities.hpp"

namespace NETWORK
{

    class ISocket
    {
    public:
        using OnRecieved = std::function<void(void)>;
        using OnAccept = std::function<void(void)>;
        virtual bool CreateSocket(void) noexcept = 0;
        virtual bool connect() noexcept = 0;
        virtual bool send(const std::string &message) noexcept = 0;
        virtual bool read(std::string &buffer, const uint16_t bufferSize) noexcept = 0;
        virtual bool isConnected(void) const noexcept = 0;
        virtual~ISocket()=default;
    };
    class IServerSocket:public ISocket
    {
        public:
        virtual bool bind(const std::string& ip, uint16_t portNumber) noexcept = 0;
        virtual bool listen() noexcept = 0;
        virtual bool accept() noexcept = 0;
        virtual SOCKET get_client_socket() const noexcept = 0;
        virtual void  close_client_socket() noexcept = 0;
        virtual ~IServerSocket() = default;
    };
}

#endif