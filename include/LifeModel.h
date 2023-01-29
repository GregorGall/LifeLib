#pragma once
#include<memory>
#include<thread>
#include<chrono>
#include<functional>

#include "Desk.h"
#include "Cell.h"
#include "LifeEngine.h"
#include "Engines/CommonEngine.h"

namespace Life {

  enum class EngineType {
    common,
    thread,
    openmp,
    cuda
  };

  class LifeModel {

  public:

  LifeModel(int rows, int cols);

  void run(std::function<void()> callBack = nullptr);

  void stop(){ proceed = false; }

  void toggleCell(int row, int col);

  void setEngine(EngineType type);

  void setDelay(std::chrono::milliseconds input) { delay = input; }

  void resize(int rows, int cols);

  void clear();

  const Desk& readData(){ return desk; }

  private:

  Desk desk;

  std::unique_ptr<LifeEngine> engine;

  std::chrono::milliseconds delay{ 0 };

  bool proceed{ true };

  };

}
