#include "gtest/gtest.h"
#include "App.h"

// Тест создает 6 глайдеров и вычисляет 100 поколений.
TEST(ModelIntegration, SwarmLife){
  App app;
  EXPECT_EQ(app.testExec(),0);
}
