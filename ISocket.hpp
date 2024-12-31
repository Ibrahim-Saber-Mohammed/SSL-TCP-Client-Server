#ifndef _ISOCKET__HPP__
#define _ISOCKET__HPP__

#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include "Utilities.hpp"

namespace NETWORK
{
    /**
    * This abstract class is an Interface providing all the behaviors required for the Sockets
    * These operations are related to all the sockets either it is a server (TCP/UDP) or a client
    */
    class ISocket
    {
    public:
        // These are represinting the types of the callbacks functions 
        using OnRecieved = std::function<void(void)>;
        using OnAccept = std::function<void(void)>;
        virtual bool CreateSocket(void) noexcept = 0;
        virtual bool connect() noexcept = 0;
        virtual bool send(const std::string &message) noexcept = 0;
        virtual bool read(std::string &buffer, const uint16_t bufferSize) noexcept = 0;
        virtual bool isConnected(void) const noexcept = 0;
        virtual~ISocket()=default;
    };
     /**
    * This abstract class is an Interface providing all the behaviors required for the Server only
    * The class extends the operations from the ISocket and add the behaviors required for the server only
    */
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
