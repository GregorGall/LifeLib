#pragma once
#include <omp.h>
#include <unordered_set>

#include "LifeEngine.h"

namespace Life {

  class OpenMPEngine: public LifeEngine {

  public:

    OpenMPEngine(Desk& desk);

    void process() override final;

  private:

    void calculate();

    void evolute();

  };

}
