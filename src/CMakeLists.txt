# Включение модуля управления условной компиляцией
include(${CMAKE_SOURCE_DIR}/CMake/AddEngine.cmake)

# Сборка статической библиотеки
aux_source_directory(. Model)
add_library(LifeModel ${Model} Engines/CommonEngine.cpp)

target_include_directories(LifeModel PRIVATE ${CMAKE_SOURCE_DIR}/include)
AddOpenMP(LifeModel)
AddThread(LifeModel)
