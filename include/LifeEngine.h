#pragma once
#include <unordered_set>

#include "Desk.h"
#include "Cell.h"

namespace Life {

  class LifeEngine {

  public:

    LifeEngine(Desk& desk): desk{ desk }{};

    void process(){ evolute(calculate()); }

    void add(Cell* cell){ aliveCells.insert(cell); }

    void remove(Cell* cell){ aliveCells.erase(cell); };

  protected:

    using CellSet = std::unordered_set<Cell*>;

    Desk& desk;
    CellSet aliveCells;

  protected:

    virtual CellSet calculate() = 0;

    virtual void evolute(CellSet cellSet) = 0;


  };

}
