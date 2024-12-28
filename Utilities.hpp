#ifndef _UTILITIES__HPP__
#define _UTILITIES__HPP__

#include <cstdio>
#include <string>
#include <errno.h>
#include <stdlib.h>
#include <cstring>
namespace NETWORK
{
#define MIN_PORT_VALUE (int)(0)
#define MAX_PORT_VALUE (int)(65535)
#define INVALID_SOCKET (int)(-1)
#define SOCKET_ERROR (int)(-1)
#define IS_FAILED_SYSCALL(val) (bool)((val) == SOCKET_ERROR)
#define IS_INVALID_SOCKET(val) (bool)((val) == INVALID_SOCKET)
#define SOCKET int
#define ERROR(msg) { \
        fprintf(stderr, "%s : %s\n", msg, strerror(errno));} \

}
template<typename T, typename... Ts>
auto make_unique(Ts&&... args)-> std::unique_ptr<T>
{
    return std::unique_ptr<T>(new T(std::forward<Ts>(args)...));
}

#endif