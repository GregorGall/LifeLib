#Тест класса клетки
add_executable(CellTest CellTest.cpp)
target_link_libraries(CellTest LifeLib gtest gtest_main)

#Тест всей модели
add_executable(LifeModelTest LifeModelTest.cpp)
target_link_libraries(LifeModelTest LifeLib gtest gtest_main)
target_include_directories(LifeModelTest PUBLIC /opt/homebrew/include)

add_test(CellTestSuit CellTest)
add_test(LifeModelTestSuit LifeModelTest)

if(CMAKE_CXX_STANDARD GREATER_EQUAL 20)
  add_subdirectory(MvcTests)
endif()
