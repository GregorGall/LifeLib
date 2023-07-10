#Тест класса клетки
add_executable(CellTest CellTest.cpp)
target_link_libraries(CellTest LifeLib gtest gtest_main)

#Тест всей модели
add_executable(LifeModelTest LifeModelTest.cpp)
target_link_libraries(LifeModelTest LifeLib gtest gtest_main)

add_test(CellTestSuit CellTest)
add_test(LifeModelTestSuit LifeModelTest)

add_subdirectory(MvcTests)
