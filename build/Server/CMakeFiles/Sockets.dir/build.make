# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ibrahim/Desktop/Sockets/Client-Server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ibrahim/Desktop/Sockets/Client-Server/build

# Include any dependencies generated for this target.
include Server/CMakeFiles/Sockets.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Server/CMakeFiles/Sockets.dir/compiler_depend.make

# Include the progress variables for this target.
include Server/CMakeFiles/Sockets.dir/progress.make

# Include the compile flags for this target's objects.
include Server/CMakeFiles/Sockets.dir/flags.make

Server/CMakeFiles/Sockets.dir/src/EventLoop.cpp.o: Server/CMakeFiles/Sockets.dir/flags.make
Server/CMakeFiles/Sockets.dir/src/EventLoop.cpp.o: ../Server/src/EventLoop.cpp
Server/CMakeFiles/Sockets.dir/src/EventLoop.cpp.o: Server/CMakeFiles/Sockets.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ibrahim/Desktop/Sockets/Client-Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Server/CMakeFiles/Sockets.dir/src/EventLoop.cpp.o"
	cd /home/ibrahim/Desktop/Sockets/Client-Server/build/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Server/CMakeFiles/Sockets.dir/src/EventLoop.cpp.o -MF CMakeFiles/Sockets.dir/src/EventLoop.cpp.o.d -o CMakeFiles/Sockets.dir/src/EventLoop.cpp.o -c /home/ibrahim/Desktop/Sockets/Client-Server/Server/src/EventLoop.cpp

Server/CMakeFiles/Sockets.dir/src/EventLoop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Sockets.dir/src/EventLoop.cpp.i"
	cd /home/ibrahim/Desktop/Sockets/Client-Server/build/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ibrahim/Desktop/Sockets/Client-Server/Server/src/EventLoop.cpp > CMakeFiles/Sockets.dir/src/EventLoop.cpp.i

Server/CMakeFiles/Sockets.dir/src/EventLoop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Sockets.dir/src/EventLoop.cpp.s"
	cd /home/ibrahim/Desktop/Sockets/Client-Server/build/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ibrahim/Desktop/Sockets/Client-Server/Server/src/EventLoop.cpp -o CMakeFiles/Sockets.dir/src/EventLoop.cpp.s

Server/CMakeFiles/Sockets.dir/src/Server.cpp.o: Server/CMakeFiles/Sockets.dir/flags.make
Server/CMakeFiles/Sockets.dir/src/Server.cpp.o: ../Server/src/Server.cpp
Server/CMakeFiles/Sockets.dir/src/Server.cpp.o: Server/CMakeFiles/Sockets.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ibrahim/Desktop/Sockets/Client-Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Server/CMakeFiles/Sockets.dir/src/Server.cpp.o"
	cd /home/ibrahim/Desktop/Sockets/Client-Server/build/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Server/CMakeFiles/Sockets.dir/src/Server.cpp.o -MF CMakeFiles/Sockets.dir/src/Server.cpp.o.d -o CMakeFiles/Sockets.dir/src/Server.cpp.o -c /home/ibrahim/Desktop/Sockets/Client-Server/Server/src/Server.cpp

Server/CMakeFiles/Sockets.dir/src/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Sockets.dir/src/Server.cpp.i"
	cd /home/ibrahim/Desktop/Sockets/Client-Server/build/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ibrahim/Desktop/Sockets/Client-Server/Server/src/Server.cpp > CMakeFiles/Sockets.dir/src/Server.cpp.i

Server/CMakeFiles/Sockets.dir/src/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Sockets.dir/src/Server.cpp.s"
	cd /home/ibrahim/Desktop/Sockets/Client-Server/build/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ibrahim/Desktop/Sockets/Client-Server/Server/src/Server.cpp -o CMakeFiles/Sockets.dir/src/Server.cpp.s

Server/CMakeFiles/Sockets.dir/src/ServerSocket.cpp.o: Server/CMakeFiles/Sockets.dir/flags.make
Server/CMakeFiles/Sockets.dir/src/ServerSocket.cpp.o: ../Server/src/ServerSocket.cpp
Server/CMakeFiles/Sockets.dir/src/ServerSocket.cpp.o: Server/CMakeFiles/Sockets.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ibrahim/Desktop/Sockets/Client-Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object Server/CMakeFiles/Sockets.dir/src/ServerSocket.cpp.o"
	cd /home/ibrahim/Desktop/Sockets/Client-Server/build/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Server/CMakeFiles/Sockets.dir/src/ServerSocket.cpp.o -MF CMakeFiles/Sockets.dir/src/ServerSocket.cpp.o.d -o CMakeFiles/Sockets.dir/src/ServerSocket.cpp.o -c /home/ibrahim/Desktop/Sockets/Client-Server/Server/src/ServerSocket.cpp

Server/CMakeFiles/Sockets.dir/src/ServerSocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Sockets.dir/src/ServerSocket.cpp.i"
	cd /home/ibrahim/Desktop/Sockets/Client-Server/build/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ibrahim/Desktop/Sockets/Client-Server/Server/src/ServerSocket.cpp > CMakeFiles/Sockets.dir/src/ServerSocket.cpp.i

Server/CMakeFiles/Sockets.dir/src/ServerSocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Sockets.dir/src/ServerSocket.cpp.s"
	cd /home/ibrahim/Desktop/Sockets/Client-Server/build/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ibrahim/Desktop/Sockets/Client-Server/Server/src/ServerSocket.cpp -o CMakeFiles/Sockets.dir/src/ServerSocket.cpp.s

Server/CMakeFiles/Sockets.dir/src/Session.cpp.o: Server/CMakeFiles/Sockets.dir/flags.make
Server/CMakeFiles/Sockets.dir/src/Session.cpp.o: ../Server/src/Session.cpp
Server/CMakeFiles/Sockets.dir/src/Session.cpp.o: Server/CMakeFiles/Sockets.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ibrahim/Desktop/Sockets/Client-Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object Server/CMakeFiles/Sockets.dir/src/Session.cpp.o"
	cd /home/ibrahim/Desktop/Sockets/Client-Server/build/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Server/CMakeFiles/Sockets.dir/src/Session.cpp.o -MF CMakeFiles/Sockets.dir/src/Session.cpp.o.d -o CMakeFiles/Sockets.dir/src/Session.cpp.o -c /home/ibrahim/Desktop/Sockets/Client-Server/Server/src/Session.cpp

Server/CMakeFiles/Sockets.dir/src/Session.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Sockets.dir/src/Session.cpp.i"
	cd /home/ibrahim/Desktop/Sockets/Client-Server/build/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ibrahim/Desktop/Sockets/Client-Server/Server/src/Session.cpp > CMakeFiles/Sockets.dir/src/Session.cpp.i

Server/CMakeFiles/Sockets.dir/src/Session.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Sockets.dir/src/Session.cpp.s"
	cd /home/ibrahim/Desktop/Sockets/Client-Server/build/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ibrahim/Desktop/Sockets/Client-Server/Server/src/Session.cpp -o CMakeFiles/Sockets.dir/src/Session.cpp.s

Server/CMakeFiles/Sockets.dir/src/ThreadPool.cpp.o: Server/CMakeFiles/Sockets.dir/flags.make
Server/CMakeFiles/Sockets.dir/src/ThreadPool.cpp.o: ../Server/src/ThreadPool.cpp
Server/CMakeFiles/Sockets.dir/src/ThreadPool.cpp.o: Server/CMakeFiles/Sockets.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ibrahim/Desktop/Sockets/Client-Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object Server/CMakeFiles/Sockets.dir/src/ThreadPool.cpp.o"
	cd /home/ibrahim/Desktop/Sockets/Client-Server/build/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Server/CMakeFiles/Sockets.dir/src/ThreadPool.cpp.o -MF CMakeFiles/Sockets.dir/src/ThreadPool.cpp.o.d -o CMakeFiles/Sockets.dir/src/ThreadPool.cpp.o -c /home/ibrahim/Desktop/Sockets/Client-Server/Server/src/ThreadPool.cpp

Server/CMakeFiles/Sockets.dir/src/ThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Sockets.dir/src/ThreadPool.cpp.i"
	cd /home/ibrahim/Desktop/Sockets/Client-Server/build/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ibrahim/Desktop/Sockets/Client-Server/Server/src/ThreadPool.cpp > CMakeFiles/Sockets.dir/src/ThreadPool.cpp.i

Server/CMakeFiles/Sockets.dir/src/ThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Sockets.dir/src/ThreadPool.cpp.s"
	cd /home/ibrahim/Desktop/Sockets/Client-Server/build/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ibrahim/Desktop/Sockets/Client-Server/Server/src/ThreadPool.cpp -o CMakeFiles/Sockets.dir/src/ThreadPool.cpp.s

# Object files for target Sockets
Sockets_OBJECTS = \
"CMakeFiles/Sockets.dir/src/EventLoop.cpp.o" \
"CMakeFiles/Sockets.dir/src/Server.cpp.o" \
"CMakeFiles/Sockets.dir/src/ServerSocket.cpp.o" \
"CMakeFiles/Sockets.dir/src/Session.cpp.o" \
"CMakeFiles/Sockets.dir/src/ThreadPool.cpp.o"

# External object files for target Sockets
Sockets_EXTERNAL_OBJECTS =

Server/libSockets.a: Server/CMakeFiles/Sockets.dir/src/EventLoop.cpp.o
Server/libSockets.a: Server/CMakeFiles/Sockets.dir/src/Server.cpp.o
Server/libSockets.a: Server/CMakeFiles/Sockets.dir/src/ServerSocket.cpp.o
Server/libSockets.a: Server/CMakeFiles/Sockets.dir/src/Session.cpp.o
Server/libSockets.a: Server/CMakeFiles/Sockets.dir/src/ThreadPool.cpp.o
Server/libSockets.a: Server/CMakeFiles/Sockets.dir/build.make
Server/libSockets.a: Server/CMakeFiles/Sockets.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ibrahim/Desktop/Sockets/Client-Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library libSockets.a"
	cd /home/ibrahim/Desktop/Sockets/Client-Server/build/Server && $(CMAKE_COMMAND) -P CMakeFiles/Sockets.dir/cmake_clean_target.cmake
	cd /home/ibrahim/Desktop/Sockets/Client-Server/build/Server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Sockets.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Server/CMakeFiles/Sockets.dir/build: Server/libSockets.a
.PHONY : Server/CMakeFiles/Sockets.dir/build

Server/CMakeFiles/Sockets.dir/clean:
	cd /home/ibrahim/Desktop/Sockets/Client-Server/build/Server && $(CMAKE_COMMAND) -P CMakeFiles/Sockets.dir/cmake_clean.cmake
.PHONY : Server/CMakeFiles/Sockets.dir/clean

Server/CMakeFiles/Sockets.dir/depend:
	cd /home/ibrahim/Desktop/Sockets/Client-Server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ibrahim/Desktop/Sockets/Client-Server /home/ibrahim/Desktop/Sockets/Client-Server/Server /home/ibrahim/Desktop/Sockets/Client-Server/build /home/ibrahim/Desktop/Sockets/Client-Server/build/Server /home/ibrahim/Desktop/Sockets/Client-Server/build/Server/CMakeFiles/Sockets.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Server/CMakeFiles/Sockets.dir/depend

