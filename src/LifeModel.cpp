#include "LifeModel.h"


Life::LifeModel::LifeModel(int rows, int cols): desk(rows, cols)
{
  setEngine(EngineType::common);
}

void Life::LifeModel::setDelay(std::chrono::milliseconds input)
{
  if(input.count() >= 0) {
      delay = input;
  }
}

void Life::LifeModel::toggleCell(int row, int col)
{
  engine->toggleCell(row, col);
}

void Life::LifeModel::setEngine(EngineType type)
{
  std::lock_guard gaurd(dataMutex);
  switch (type) {
    case EngineType::common:
      engine = std::make_unique<CommonEngine>(desk);
      break;
    case EngineType::thread:
//      engine = std::make_unique<ThreadEngine>(desk);
      break;
    case EngineType::openmp:
//      engine = std::make_unique<OpenMPEngine>(desk);
      break;
    case EngineType::cuda:
      break;
    default:
      engine = std::make_unique<CommonEngine>(desk);
  }
}

void Life::LifeModel::run(std::function<void()> callBack)
{
  while(proceed) {
    std::this_thread::sleep_for(delay);
    std::lock_guard gaurd(dataMutex);
    engine->process();
    if(callBack){ callBack(); }
  }

  proceed = true;
}
