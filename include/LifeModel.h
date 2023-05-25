#pragma once
#include <memory>
#include <thread>
#include <mutex>
#include <chrono>
#include <functional>

#include "CommonEngine.h"
#include "OpenMPEngine.h"
#include "ThreadEngine/ThreadEngine.h"

namespace Life {

  enum class EngineType {
    common,
    thread,
    openmp,
    cuda
  };

  class LifeModel {

  public:

    explicit LifeModel(int rows = 0, int cols = 0);

    const Desk& readData() const;

    const std::chrono::milliseconds& readDelay() const;

    void run(std::function<void()> callBack = nullptr);

    void stop(){ proceed = false; }

    void toggleCell(int row, int col);

    void setEngine(EngineType type);

    void setDelay(std::chrono::milliseconds input);

    void resize(int rows, int cols);

    void clearDesk();

    template<class container>
    void toggleGroup(const container& cellGroup )
    {
      std::lock_guard gaurd(dataMutex);
      for(auto& cell: cellGroup) {
        toggleCell(cell.first, cell.second);
      }
    }

  private:

    Desk desk;

    std::mutex dataMutex;

    std::unique_ptr<LifeEngine> engine{ nullptr };

    std::chrono::milliseconds delay{ 0 };

    bool proceed{ true };

  };

}
