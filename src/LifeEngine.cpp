#include "LifeEngine.h"

Life::LifeEngine::LifeEngine(Desk &desk): desk{ desk }
{
}

void Life::LifeEngine::reset()
{
}

void Life::LifeEngine::toggleCell(int row, int col)
{
  desk(row, col).toggle();
}

