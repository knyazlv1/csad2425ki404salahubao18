cmake_minimum_required(VERSION 3.10)

project(ClientTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(D:/csad/client/include)

add_executable(client_main
    D:/CSAD/client/src/main.cpp
    D:/CSAD/client/src/game.cpp
    D:/CSAD/client/src/serial.cpp
)

# Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(TestProject
    D:/CSAD/client/tests/test_game.cpp
    D:/CSAD/client/tests/test_serial.cpp
   
)

target_link_libraries(TestProject PRIVATE ${GTEST_LIBRARIES} pthread)

enable_testing()
add_test(NAME ClientTests COMMAND TestProject)