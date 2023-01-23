# Сборка исполняемого файла тестов
add_executable(MainTest mainTest.cpp)
target_link_libraries(MainTest LifeModel)
target_include_directories(MainTest PUBLIC ${CMAKE_SOURCE_DIR}/include)
