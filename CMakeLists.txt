# Мінімальна версія CMake
cmake_minimum_required(VERSION 3.10)

# Назва проекту
project(ClientServerProject)

# Встановлюємо стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Додати шлях до заголовків
include_directories(${CMAKE_SOURCE_DIR}/client/include)


# Створення виконуваного файлу з вихідних файлів
add_executable(client
    ${CMAKE_SOURCE_DIR}/client/src/csad_lab2_sao.cpp
    ${CMAKE_SOURCE_DIR}/client/src/serial_communication.cpp
)


