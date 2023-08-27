# Сборка теста модели в составе приложения
aux_source_directory(src MVC)
add_executable(MvcTest MvcTest.cpp ${MVC})

target_include_directories(MvcTest PRIVATE include)
target_link_libraries(MvcTest LifeLib gtest gtest_main)

add_test(MvcTestSuit MvcTest)

# Сборка консольного приложения Life для ручного тестирования
add_executable(MvcManualTest MvcManualTest.cpp ${MVC})

target_include_directories(MvcManualTest PRIVATE include)
target_link_libraries(MvcManualTest LifeLib)
