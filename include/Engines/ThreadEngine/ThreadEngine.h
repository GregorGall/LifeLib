#pragma once
#include <memory>
#include <thread>
#include <vector>

#include "barrier.h"
#include "ThreadPull.h"
#include "LifeEngine.h"

namespace Life {

  class ThreadEngine: public LifeEngine {

  public:

    ThreadEngine(Desk& desk);

    void process() override final;

  private:

    void partProcess(int initPoint, int endPoint);

    void calculate(int initPoint, int endPoint);

    void evolute(int initPoint, int endPoint);

  private:

    barrier syncPoint;
    ThreadPull pull;
    std::vector<std::future<void>> results;

  };

}
