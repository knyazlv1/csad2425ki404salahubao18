# Minimal version of CMake
cmake_minimum_required(VERSION 3.10)

# Name of project
project(ClientServerProject)

# Set standard C++
set(CMAKE_CXX_STANDARD 17)


# Specify directories with header files
include_directories(${CMAKE_SOURCE_DIR}/client/include)

# add an executable file for the client
add_executable(client
    ${CMAKE_SOURCE_DIR}/client/src/CSAD_lab2.cpp
    ${CMAKE_SOURCE_DIR}/client/src/SerialPort.cpp
)

# specify that the Windows library should be used
if(WIN32)
    target_link_libraries(client PRIVATE ws2_32)
endif()
