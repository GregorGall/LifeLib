add_executable(CellTest CellTest.cpp)
target_link_libraries(CellTest LifeLib gtest gtest_main)

add_test(CellTestSuit CellTest)
