# Мінімальна версія CMake
cmake_minimum_required(VERSION 3.10)

# Назва проекту
project(ClientServerProject)

# Встановлюємо стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Вкажіть шлях до папки Boost із заголовками і бібліотеками
set(BOOST_ROOT "D:/Programs/boost_1_86_0")
set(BOOST_INCLUDEDIR "D:/Programs/boost_1_86_0/boost")          # Шлях до папки з заголовками Boost
set(BOOST_LIBRARYDIR "D:/Programs/boost_1_86_0/lib64-msvc-14.3") # Шлях до папки з бібліотеками Boost

# Пошук бібліотеки Boost (необхідно для Boost.Asio)
find_package(Boost REQUIRED COMPONENTS system)

# Додаємо шлях до заголовків
include_directories(${CMAKE_SOURCE_DIR}/client/include ${Boost_INCLUDE_DIRS})

# Створення виконуваного файлу з вихідних файлів
add_executable(client
    ${CMAKE_SOURCE_DIR}/client/src/csad_lab2_sao.cpp
    ${CMAKE_SOURCE_DIR}/client/src/serial_communication.cpp
)

# Лінкуємо бібліотеку Boost із виконуваним файлом
target_link_libraries(client ${Boost_LIBRARIES})
