#ifndef SERVER_SOCKET__HPP__
#define SERVER_SOCKET__HPP__

#include <Socket/ISocket.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <openssl/opensslconf.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <Server/Utilities.hpp>

namespace NETWORK
{
    constexpr uint8_t m_numberOfClients{10U};
    /**
    * ServerSocket is a class that wrapps the TCP Server Socket operations
    * The class is implementing the IServerSocket interface
    * The class is responsible for implementing all the Server operations required to create, 
    * Connect, read, write to a TCP socket
    */
    class ServerSocket : public IServerSocket
    {
    public:
         /**
            * @description: constructor that takes the ip address, and port number 
            *               these info are used in order to the host (Server) to listen to 
            * @param[in]: uint16_t portNumber
            *             An integer number represinting the port to receive data from
            * @param[in]: const std::string& ip
            *              A string represing the ip address to the host to accept connections to 
            *              this IP
            *
        */
        ServerSocket(uint16_t portNumber, const std::string& ip);
        /**
            * @name : CreateSocket 
            * @description: A method that create the TCP socket it self using the socket system call function
            *               And return an Indication representing whether or not the socket system call 
            *               was excuted successfully.
            *         
            * @param[in]: None
            * @param[out]: bool 
            *             An Indication whether or not a socket was created correctly
            * @note:
            *    The method is intended to be noexcept (that the method is not going to emit any exceptions)
            *
        */
        virtual bool CreateSocket(void) noexcept override;
        /**
            * @name : connect 
            * @description: A method that connects to the socket by binding the socket to the Information 
            *                provided at the constructor and start listining to the socket.
            *                The method returns an Indication whether or not the binding operation or the listen operation
            *                were not successfully excuted.
            *         
            * @param[in]: None
            * @param[out]: bool 
            *             An Indication whether or not a the method was not successfully excuted.
            * @note:
            *    The method is intended to be noexcept (that the method is not going to emit any exceptions).
            *
        */
        virtual bool connect() noexcept override;
        /**
            * @name : send 
            * @description: A method that send the msg to the client. it writes the msg to the 
            *                Socket file descriptor. it uses write system call.
            *         
            * @param[in]: const std::string &message
            *             A message string buffer to be sent 
            * @param[out]: bool
            *             An Indication whether or not the message was sent successfully.
            * @note:
            *    The method is intended to be noexcept (that the method is not going to emit any exceptions).
            *
        */
        virtual bool send(const std::string &message) noexcept override;
        /**
            * @name : read 
            * @description: A method that recieve a msg from the client. it reads the msg that is
            *               coming to Socket file descriptor. it uses read system call.
            *               If the data received is less than the number of bytes user was excepecting
            *               The read system call returns the actual number of bytes recieved
            *         
            * @param[in]: const std::string &message
            *             A message string buffer to store the received data inside
            * @param[in]: uint16_t bufferSize
            *             An integer value representing the excepected number of bytes to be recieved
            *             
            * @param[out]: bool
            *             An Indication whether or not the message was recieved successfully.
            * @note:
            *    The method is intended to be noexcept (that the method is not going to emit any exceptions).
            *
        */
        virtual bool read(std::string &buffer, uint16_t bufferSize) noexcept override;
        /**
            * @name : accept 
            * @description: A method that listens to the socket and once there is a new connction is 
            *               avalible it accepts the connection and store the client FD.
            *         
            * @param[in]: None
            * @param[out]: bool
            *             An Indication whether or not the connection was accepted successfully.
            * @note:
            *    The method is intended to be noexcept (that the method is not going to emit any exceptions).
            *
        */
        virtual bool accept(void)noexcept override;
        /**
            * @name : listen 
            * @description: A method that configure and tell the socket that it is ready to 
            *               start listening to Server Socket created. 
            *               Server listens to the socket for either new connection or data is ready to be 
            *               either sent or recieved.
            *         
            * @param[in]: None
            * @param[out]: bool
            *             An Indication whether or not the socket listens operation was excuted successfully.
            * @note:
            *    The method is intended to be noexcept (that the method is not going to emit any exceptions).
            *
        */
        virtual bool listen(void) noexcept override;
        /**
            * @name : get_client_socket 
            * @description: A method that returns the cliend fd which was accepted by the accept nethod
            *               This client fd is used to communicate with this client and it's unique for each client.
            *         
            * @param[in]: None
            * @param[out]: SOCKET
            *             An integer number representing the client fd.
            * @note:
            *    The method is intended to be noexcept (that the method is not going to emit any exceptions).
            * @note:
            *    The method is intended to be const (that the method is not going to modify any internal properties).
            *
        */
        virtual SOCKET get_client_socket(void)const noexcept override;
        /**
            * @name : close_client_socket 
            * @description: A method that closes the connection with the client connected to the server.
            *         
            * @param[in]: None
            * @param[out]: None
            *     
            * @note:
            *    The method is intended to be noexcept (that the method is not going to emit any exceptions).
            *
        */
        virtual void close_client_socket(void) noexcept override;
        /**
            * @name : ~ServerSocket 
            * @description: The class destructor and is used to perfectly cleen and free all the resources of the class.
            *         
            * @param[in]: None
            * @param[out]: None
            *     
            * @note:
            *    The method is intended to be noexcept (that the method is not going to emit any exceptions).
            *
        */
        virtual ~ServerSocket()noexcept;
        /**
            * @name : bind 
            * @description: A method that bindes the socket with specific port number and ip address.
            *               This method is either called by the user and then the user also calls the listen method
            *                or the user calls only the connect method and it does these operatioon for him.
            *         
            * @param[in]: uint16_t portNumber
            *             An integer number represinting the port to receive data from
            * @param[in]: const std::string& ip
            *              A string represing the ip address to the host to accept connections to 
            * @param[out]: bool 
            *             An Indication whether or not a the method was not successfully excuted.
            * @note:
            *    The method is intended to be noexcept (that the method is not going to emit any exceptions).
            *
        */
        virtual bool bind(const std::string& ip, uint16_t portNumber)noexcept override;
        virtual bool isConnected(void) const noexcept override;
        virtual SOCKET git_server_socket(void) const noexcept override;
        
    private:
        bool m_isConnectedServer{false};
        /**
            * @name : isValidPortNumber 
            * @description: function is used to validate the port number and ensures that the port number is between 
                            0 and 65535.
            * @param[in]: uint16_t portNumber
            *             An integer number represinting the port to receive data from
            * @param[out]: bool 
            *             An Indication whether or not a the port number is valid to be used.
            * @note:
            *    The method is intended to be noexcept (that the method is not going to emit any exceptions).
            *
        */
        bool isValidPortNumber(uint16_t portNumber)const noexcept;
        // variable used to hold the server fd
        SOCKET m_socketfd{-1};
        // variable to store the port number
        uint16_t m_port;
        // variable to store the ip address
        std::string m_address;
        // variable to store the accepted client fd
        SOCKET m_client{-1};
    };
}

#endif
