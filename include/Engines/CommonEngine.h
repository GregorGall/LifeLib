#pragma once
#include <unordered_set>

#include "LifeEngine.h"

namespace Life {

  class CommonEngine: public LifeEngine {

  public:

    CommonEngine(Desk& desk);

    void process() override final { evolute(calculate()); }

    void toggleCell(int row, int col) override final;

    void add(Cell* cell) { aliveCells.insert(cell); }

    void remove(Cell* cell) { aliveCells.erase(cell); }

  private:

    using CellSet = std::unordered_set<Cell*>;

    CellSet aliveCells;

  private:

    CellSet calculate();

    void evolute(CellSet cellSet);

  };

}
