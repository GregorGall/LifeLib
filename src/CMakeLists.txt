# Сборка статической библиотеки
aux_source_directory(Engines Engines)
aux_source_directory(. Main)

add_library(LifeModel ${Main} ${Engines})
target_include_directories(LifeModel PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(LifeModel PRIVATE "${OpenMP_CXX_FLAGS}")
target_compile_options(LifeModel PRIVATE "${OpenMP_CXX_FLAGS}")
