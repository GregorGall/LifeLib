# Включение модуля управления условной компиляцией
include(${PROJECT_SOURCE_DIR}/CMake/AddEngine.cmake)

# Сборка статической библиотеки
aux_source_directory(. Model)
add_library(LifeLib ${Model} Engines/CommonEngine.cpp)
AddOpenMP(LifeLib)
AddThread(LifeLib)

target_include_directories(LifeLib PUBLIC ${PROJECT_SOURCE_DIR}/include
                                          ${PROJECT_SOURCE_DIR}/include/Engines)
# Сборка тестов
add_subdirectory(tests)
