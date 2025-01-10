cmake_minimum_required(VERSION 3.10.0)

project(Client_Server_SSL)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Organize applications, libraries, etc. in folders in the IDE.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Don't add the goofy "d" postfix for debug builds of libraries.
set(CMAKE_DEBUG_POSTFIX "")

add_subdirectory(Server)
set(This ServerApp)

add_executable(${This} Server/src/main.cpp)
set_target_properties(${This} PROPERTIES FOLDER Applications)
target_link_libraries(${This} PUBLIC Sockets)

if(UNIX AND NOT APPLE)
    target_link_libraries(${This} PRIVATE -static-libstdc++ -lssl -lcrypto)
endif(UNIX AND NOT APPLE)



