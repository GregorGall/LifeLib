#include <Engines/ThreadEngine/ThreadEngine.h>

void Life::ThreadEngine::process()
{
  int blockNum = desk.size() / threadNum;
  for(int i = 0; i < threadNum; ++i) {
    int initPoint = i * blockNum;
    int endPoint = initPoint + blockNum;
    pull[i] = jthread(&ThreadEngine::partProcess, std::ref(*this), initPoint, endPoint);
  }
}

void Life::ThreadEngine::partProcess(int initPoint, int endPoint)
{
  calculate(initPoint, endPoint);
  syncPoint.wait();
  evolute(initPoint,endPoint);
}

void Life::ThreadEngine::calculate(int initPoint, int endPoint)
{
  for(int i = initPoint; i < endPoint; ++i) {
      auto& cell = desk[i];
      if(cell) {
        for(auto neighbour: desk.getNeighbours(&cell)) {
          neighbour->increment();
        }
      }
  }
}

void Life::ThreadEngine::evolute(int initPoint, int endPoint)
{
  for(int i = initPoint; i < endPoint; ++i) {
      desk[i].evolute();
  }
}

