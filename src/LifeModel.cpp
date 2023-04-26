#include "LifeModel.h"


Life::LifeModel::LifeModel(int rows, int cols): desk(rows, cols)
{
  setEngine(Life::EngineType::common);
}

const Life::Desk &Life::LifeModel::readData()
{
  return desk;
}

const std::chrono::milliseconds& Life::LifeModel::readDelay()
{
  return delay;
}

void Life::LifeModel::setDelay(std::chrono::milliseconds input)
{
  if(input.count() >= 0) {
      delay = input;
  }
}

void Life::LifeModel::resize(int rows, int cols)
{
  desk.resize(rows, cols);
  engine->reset();
}

void Life::LifeModel::clearDesk()
{
  std::lock_guard gaurd(dataMutex);
  desk.clear();
  engine->reset();
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
      USE_THREAD(engine = std::make_unique<ThreadEngine>(desk);)
      break;
    case EngineType::openmp:
      USE_OPENMP(engine = std::make_unique<OpenMPEngine>(desk);)
      break;
    case EngineType::cuda:
      USE_CUDA()
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
