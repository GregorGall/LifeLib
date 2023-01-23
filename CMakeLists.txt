cmake_minimum_required(VERSION 3.5)

project(LifeLib VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Флаг сборки тестов
option(TEST "Build tests" ON)
message(STATUS "Build tests ${TEST}")

# Подключение каталога с библиотекой
add_subdirectory(src)

# Подключение каталога с тестами
if(TEST)
  add_subdirectory(test)
endif()

