# Включение модуля управления условной компиляцией
include(${PROJECT_SOURCE_DIR}/CMake/AddEngine.cmake)

# Сборка статической библиотеки
aux_source_directory(. Model)
add_library(LifeLib ${Model} Engines/CommonEngine.cpp)

target_include_directories(LifeLib PRIVATE ${PROJECT_SOURCE_DIR}/include)
AddOpenMP(LifeLib)
AddThread(LifeLib)
