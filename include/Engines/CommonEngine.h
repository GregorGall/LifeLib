#pragma once
#include "LifeEngine.h"

namespace Life {

  class CommonEngine: public LifeEngine {

  public:

    CommonEngine(Desk& desk): LifeEngine(desk) {};

  private:

    virtual CellSet calculate() override final;

    virtual void evolute(CellSet cellSet) override final;

  };

}
