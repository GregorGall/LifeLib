#pragma once

#include "Desk.h"
#include "Cell.h"

namespace Life {

  class LifeEngine {

  public:

    LifeEngine(Desk& desk): desk{ desk }
    {
    }

    virtual void process() = 0;

    virtual void toggleCell(int row, int col) { desk(row, col).toggle(); }

  protected:

    Desk& desk;

  };

}
