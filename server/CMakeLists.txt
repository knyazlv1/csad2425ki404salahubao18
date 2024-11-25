cmake_minimum_required(VERSION 3.10)
project(ServerTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_server
    Test_server/test_server.cpp
    csad_server5/Source Files/server.cpp
)

include_directories(include)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

target_compile_definitions(TestServer PRIVATE TEST_ENVIRONMENT)

target_link_libraries(TestServer PRIVATE ${GTEST_LIBRARIES} pthread)

add_executable(server_main
    src/main.cpp
    src/server.cpp
)

target_include_directories(server_main PRIVATE include)