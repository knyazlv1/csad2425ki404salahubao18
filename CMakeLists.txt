# Мінімальна версія CMake
cmake_minimum_required(VERSION 3.15)

# Назва проекту
project(ClientApp)

# Вказати стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Додати шлях до заголовків
include_directories(include)

# Додати всі вихідні файли
file(GLOB SOURCES "src/*.cpp")

# Створення виконуваного файлу з вихідних файлів
add_executable(ClientApp ${SOURCES})

# Якщо використовуються бібліотеки, можна додати їх тут
# Наприклад: target_link_libraries(ClientApp serial)
