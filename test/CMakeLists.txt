# Сборка основных тестов
aux_source_directory(testMVC/src MVC)
add_executable(main mainTest.cpp ${MVC})

target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIRECTORY}/include testMVC/include)
target_link_libraries(main PUBLIC LifeModel)
