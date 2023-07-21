cmake_minimum_required(VERSION 3.5)

project(LifeLib VERSION 1.0.0 LANGUAGES CXX)

# Минимальная версия для сборки 17, в этом случае будет собрана только библиотека и тесты.
# Для сборки консольного приложения необходим 20 стандарт.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Флаг сборки тестов
option(TEST "Build tests" ON)
message(STATUS "Build tests ${TEST}")
enable_testing()

# Флаг сборки benchmark
option(BENCHMARK "Build benchmark" ON)

# Подключение каталога с библиотекой
add_subdirectory(src)
