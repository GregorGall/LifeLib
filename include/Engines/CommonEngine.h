#pragma once
#include <unordered_set>

#include "LifeEngine.h"

namespace Life {

  class CommonEngine: public LifeEngine {

    using CellSet = std::unordered_set<Cell*>;

  public:

    CommonEngine(Desk& desk);

    void add(Cell* cell);

    void remove(Cell* cell);

    void reset() override final;

    void process() override final;

    void toggleCell(int row, int col) override final;

  private:

    CellSet aliveCells;

  private:

    void init();

    CellSet calculate();

    void evolute(CellSet cellSet);

  };

}
