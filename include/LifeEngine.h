#pragma once

#include "Desk.h"
#include "Cell.h"

#ifdef NO_OPENMP
  #define USE_OPENMP(expr)
#else
  #define USE_OPENMP(expr) expr
#endif

#ifdef NO_THREAD
  #define USE_THREAD(expr)
#else
  #define USE_THREAD(expr) expr
#endif

#ifdef NO_CUDA
  #define USE_CUDA(expr)
#else
  #define USE_CUDA(expr) expr
#endif

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
