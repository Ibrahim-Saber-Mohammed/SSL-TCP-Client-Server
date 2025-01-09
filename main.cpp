#include "ServerSocket.hpp"
#include "Utilities.hpp"
#include "Server.hpp"
#include <sys/select.h>

int main(int argc, char *argv[])
{
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
    SSL_Warpper ssl;
    std::unique_ptr<IServerSocket>l_server(new ServerSocket( "127.0.0.1", 8080));
    NETWORK::TCP_Server server(ssl, std::move(l_server));

    server.run();
    return 0;
}