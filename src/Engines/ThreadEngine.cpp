#include <Engines/ThreadEngine/ThreadEngine.h>

Life::ThreadEngine::ThreadEngine(Desk &desk): LifeEngine(desk)
{
  // проверку на 0 пожалуйста
  if( desk.size() > 1000 ) { threadNum = std::thread::hardware_concurrency()/2; }
  pull.resize(threadNum);
  syncPoint.reset(threadNum);
}

void Life::ThreadEngine::process()
{
  int tailNum = desk.size() % threadNum;
  int blockNum = desk.size() / threadNum;
  int initPoint = 0;
  int endPoint = blockNum + tailNum;

  if(pull[0].joinable()) {
    for(int i = 0; i < threadNum; ++i) { pull[i].join(); }
  }

  // переделать в нормальный pull
  pull[0] = jthread(&ThreadEngine::partProcess, std::ref(*this), initPoint, endPoint);
  for(int i = 1; i < threadNum; ++i) {
    initPoint = endPoint;
    endPoint += blockNum;
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

