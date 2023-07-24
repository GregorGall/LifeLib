# Функция добавляет в source файлы OpenMPEngine.cpp и линкует OpenMP с целью
function(AddOpenMP target)
  find_package(OpenMP)
  if(OpenMP_FOUND)
    target_sources(${target} PRIVATE Engines/OpenMPEngine.cpp)
    target_link_libraries(${target} PRIVATE "${OpenMP_CXX_FLAGS}")
    target_compile_options(${target} PRIVATE "${OpenMP_CXX_FLAGS}")
  endif()
  message(STATUS "Use OpenMP engine ${OpenMP_FOUND}")
  target_compile_definitions(${target} PRIVATE "NO_OPENMP")
endfunction()

# Функция добавляет в source файлы ThreadEngine.cpp
function(AddThread target)
  if(CMAKE_CXX_STANDARD GREATER_EQUAL 17)
    message(STATUS "Use Thread engine TRUE")
    target_sources(${target} PRIVATE Engines/ThreadEngine.cpp)
  else()
    message(STATUS "Use Thread engine FALSE")
    target_compile_definitions(${target} PRIVATE "NO_THREAD")
  endif()
endfunction()
