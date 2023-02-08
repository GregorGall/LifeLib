#pragma once
#include <memory>
#include <thread>
#include <vector>

#include "barrier.h"
#include "jthread.h"
#include "LifeEngine.h"

namespace Life {

  class ThreadEngine: public LifeEngine {

  public:

    ThreadEngine(Desk& desk): LifeEngine(desk)
    {
        if( desk.size() > 1000 ) { threadNum = std::thread::hardware_concurrency()/2; }
        pull.resize(threadNum);
        syncPoint.reset(threadNum);
    }

    void process() override final;

  private:

    void partProcess(int initPoint, int endPoint);

    void calculate(int initPoint, int endPoint);

    void evolute(int initPoint, int endPoint);

  private:

    int threadNum{ 1 };
    barrier syncPoint;
    std::vector<jthread> pull;

  };

}
