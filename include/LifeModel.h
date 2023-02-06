#pragma once
#include <memory>
#include <thread>
#include <mutex>
#include <chrono>
#include <functional>

#include "Desk.h"
#include "Cell.h"
#include "LifeEngine.h"
#include "Engines/CommonEngine.h"
#include "Engines/OpenMPEngine.h"
#include "Engines/ThreadEngine/ThreadEngine.h"

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

  const Desk& readData(){ return desk; }

  std::chrono::milliseconds readDelay(){ return delay; }

  void run(std::function<void()> callBack = nullptr);

  void stop(){ proceed = false; }

  void toggleCell(int row, int col);

  void setEngine(EngineType type);

  void setDelay(std::chrono::milliseconds input);

  void resize(int rows, int cols);

  void clear();

  template<class container>
  void toggleGroup(container cellGroup )
  {
    std::lock_guard gaurd(dataMutex);
    for(auto& cell: cellGroup) {
      toggleCell(cell.first, cell.second);
    }
  }

  private:

  Desk desk;

  std::mutex dataMutex;

  std::unique_ptr<LifeEngine> engine;

  std::chrono::milliseconds delay{ 0 };

  bool proceed{ true };

  };

}
