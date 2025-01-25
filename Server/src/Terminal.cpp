#include <iostream>
#include <string>
namespace NETWORK{
class Terminal
{
    private:
        // ANSI escape codes for colors
    static constexpr char*  BLACK = "\033[30m";
    static constexpr char*  RED = "\033[31m";
    static constexpr char*  GREEN = "\033[32m";
    static constexpr char*  YELLOW = "\033[33m";
    static constexpr char*  BLUE = "\033[34m";
    static constexpr char*  MAGENTA = "\033[35m";
    static constexpr char*  CYAN = "\033[36m";
    static constexpr char*  WHITE = "\033[37m";
    static constexpr char*  RESET = "\033[0m";
public:
    void showTitle(const std::string &title);
    void printErrorMsg(const std::string &msg);
    void printConnectMsg(const std::string &msg);
    void printConnectPort(const std::string &msg , int port);
    void printWarningMsg(const std::string &msg);
    void printRecvMsg(const std::string &msg);
    void printSentMsg(const std::string &msg);
    void printMsg(const std::string &msg);
};
void Terminal::showTitle(const std::string &title)
{
    std::cout << BLUE << std::string(60,'-') << std::endl;
    std::cout << std::string(27,'-') << title << std::string(27,'-') << std::endl;
    std::cout << std::string(60,'-') << RESET << std::endl;
}

void Terminal::printMsg(const std::string &msg) {std::cout << WHITE << msg << RESET ; }

void Terminal::printErrorMsg(const std::string &msg) { std::cerr << RED << msg << RESET ; }

void Terminal::printConnectMsg(const std::string &msg) { std::cout << GREEN << msg << RESET ; }

void Terminal::printConnectPort(const std::string &msg , int port) { std::cout << GREEN << msg << port << RESET << std::endl; }

void Terminal::printWarningMsg(const std::string &msg) { std::cout << YELLOW << msg << RESET ; }

void Terminal::printRecvMsg(const std::string &msg) { std::cout << MAGENTA << msg << RESET ; }

void Terminal::printSentMsg(const std::string &msg) { std::cout << BLUE << msg << RESET ; }
}