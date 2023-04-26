# Сборка основных тестов
aux_source_directory(testMVC/src MVC)
add_executable(main mainTest.cpp ${MVC})

target_include_directories(main PRIVATE testMVC/include)
target_link_libraries(main PRIVATE LifeLib)
