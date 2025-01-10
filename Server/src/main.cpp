#include <Socket/ServerSocket.hpp>
#include <Server/Utilities.hpp>
#include <Server/Server.hpp>
#include <sys/select.h>

int main(int argc, char *argv[])
{
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
    std::cout << "Welcome to our Server App\n";
    std::unique_ptr<NETWORK::IServerSocket>l_server(new NETWORK::ServerSocket(8080, "127.0.0.1"));
    NETWORK::Server server(std::move(l_server));
    server.run();
    return 0;
}