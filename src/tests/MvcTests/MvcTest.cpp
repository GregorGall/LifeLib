#include "gtest/gtest.h"
#include "App.h"

// Тест создает 6 глайдеров вычисляет 100 поколений, потом необходимо добавить проверку на конечное расположение
TEST(ModelIntegration, SwarmLife){
  App app;
  EXPECT_EQ(app.testExec(),0);
}
