# Включение модуля управления условной компиляцией
include(${PROJECT_SOURCE_DIR}/CMake/AddEngine.cmake)

# Сборка статической библиотеки
aux_source_directory(. Model)
add_library(LifeLib ${Model} Engines/CommonEngine.cpp)
AddOpenMP(LifeLib)
AddThread(LifeLib)

target_compile_options(LifeLib PRIVATE -Wall -Wextra)
target_include_directories(LifeLib PUBLIC ${PROJECT_SOURCE_DIR}/include
                                          ${PROJECT_SOURCE_DIR}/include/Engines)
# Сборка тестов
if(TEST)

# Несовместимо с thread
  target_compile_options(LifeLib PRIVATE -fsanitize=address)
  target_link_options(LifeLib PUBLIC -fsanitize=address)

# Несовместимо с address
#  target_compile_options(LifeLib PRIVATE -fsanitize=thread)
#  target_link_options(LifeLib PUBLIC -fsanitize=thread)

  find_package(GTest REQUIRED)
  add_subdirectory(tests)

endif()

# Сборка benchmark для расчетных движков
if(BENCHMARK)
  find_package(benchmark REQUIRED)
  add_subdirectory(benchmark)
endif()
