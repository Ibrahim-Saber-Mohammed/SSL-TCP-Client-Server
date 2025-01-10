cmake_minimum_required(VERSION 3.10.0)

set(This Sockets)
set(Sources
    include/Socket/ServerSocket.hpp
    include/Socket/ISocket.hpp
    include/Socket/EventLoop.hpp
    include/SessionManager/Session.hpp
    include/SessionManager/SSL_Wrapper.hpp
    include/Server/Server.hpp
    include/Server/Utilities.hpp
    include/Server/ThreadSafetyQueue.hpp
    src/EventLoop.cpp
    src/Server.cpp
    src/ServerSocket.cpp
    src/Session.cpp
)

add_library(${This} ${Sources})
set_target_properties(${This} PROPERTIES FOLDER Libraries)
target_include_directories(${This} PUBLIC include)
if(UNIX)
    target_link_libraries(${This} PUBLIC pthread)
endif(UNIX)
