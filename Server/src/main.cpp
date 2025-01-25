#include <Socket/ServerSocket.hpp>
#include <Server/Utilities.hpp>
#include <Server/Server.hpp>
#include <sys/select.h>
#include <string>

constexpr size_t NUMBER_OF_THREADS = 5;
void OnReceivedCallBack(const std::string& message)
{
     // Process the message and take action
        if (message == "facebook"){
            // printMsg("Openning facebook...\n");
            // openFacebook();
        }else if (message == "whatsapp") {
            // printMsg("Openning whatsapp...\n");
            // openWhatsapp();
        }else if (message == "github") {
            // printMsg("Openning github...\n");
            // openGithub();
        }else if (message == "linkedin") {
            // printMsg("Openning linkedin...\n");
            // openLinkedin();
        }else if (message == "youtube") {
            // printMsg("Openning youtube...\n");
            // openYoutube();
        }else if (message == "calculator") {
            // printMsg("Openning calculator...\n");
            // openCalculator();
        }else if (message == "vscode") {
            // printMsg("Openning vscode...\n");
            // openVSCode();
        }else if (message == "exit") {
            // printMsg("Exiting...\n");
        }else{
            // printMsg("Unknown message");
        }

        // Send a response to the client
        std::string response = message + " is opened!";
        // sendToClient(response);
}
void onWriteCallBack(void)
{

}
int main(int argc, char *argv[])
{
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
    std::cout << "Welcome to our Server App\n";
    std::unique_ptr<NETWORK::IServerSocket> l_server = std::make_unique<NETWORK::ServerSocket>(8080, "127.0.0.1");
    auto threadPool = std::make_shared<NETWORK::ThreadPool>(NUMBER_OF_THREADS);
    auto eventLoop = std::make_shared<NETWORK::EventLoop>();
    NETWORK::Server server(std::move(l_server), 
                        threadPool,
                        eventLoop
                );
    server.run();
    return 0;
}