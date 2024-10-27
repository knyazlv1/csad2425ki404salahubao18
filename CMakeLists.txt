# Мінімальна версія CMake
cmake_minimum_required(VERSION 3.10)

# Назва проекту
project(ClientServerProject)

# Встановлюємо стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Вказуємо директорію з заголовочними файлами
include_directories(${CMAKE_SOURCE_DIR}/client/include)

# Додаємо виконуваний файл для клієнта
add_executable(client
    ${CMAKE_SOURCE_DIR}/client/src/CSAD_lab2.cpp
    ${CMAKE_SOURCE_DIR}/client/src/SerialPort.cpp
)