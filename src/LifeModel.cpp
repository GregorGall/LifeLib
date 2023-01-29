#pragma once

#include "LifeModel.h"


Life::LifeModel::LifeModel(int rows, int cols): desk(rows, cols)
{
  setEngine(EngineType::common);
}

void Life::LifeModel::toggleCell(int row, int col)
{
  auto& cell = desk(row, col);
  cell.toggle() ? engine->add(&cell) : engine->remove(&cell);
}

void Life::LifeModel::setEngine(EngineType type)
{
  switch (type) {
    case EngineType::common:
      engine = std::make_unique<CommonEngine>(desk);
      break;
    case EngineType::thread:
      break;
    case EngineType::openmp:
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
    engine->process();
    if(callBack){ callBack(); }
    std::this_thread::sleep_for(delay);
  }

  proceed = true;
}
