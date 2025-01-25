#ifndef _Server__HPP___
#define _Server__HPP___

#include <memory>
#include <Socket/ServerSocket.hpp>
#include <SessionManager/Session.hpp>
#include <Socket/EventLoop.hpp>
#include <Server/ThreadPool.hpp>

namespace NETWORK
{
    class Server
    {
    public:
        // types
        using OnRecieved = std::function<void(std::unique_ptr<std::string>)>;
        using OnAccept = std::function<void(void)>;
        Server(std::unique_ptr<IServerSocket> ServerStartegy, std::shared_ptr <ThreadPool> _threadPool,
                    std::shared_ptr <EventLoop>_eventLoop);
        void run();

    private:
       void do_accept(void);
    // members
        std::shared_ptr<IServerSocket> m_Server;
        std::shared_ptr <ThreadPool> m_threadPool;
        std::shared_ptr<EventLoop> m_eventloop{nullptr};
    };
}

#endif