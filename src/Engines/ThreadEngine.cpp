#include <Engines/ThreadEngine/ThreadEngine.h>

Life::ThreadEngine::ThreadEngine(Desk &desk): LifeEngine(desk)
{
  syncPoint.reset(pull.size());
}

void Life::ThreadEngine::process()
{
  int threadNum = pull.size();
  int tailNum = desk.size() % threadNum;
  int blockNum = desk.size() / threadNum;
  int initPoint = 0;
  int endPoint = blockNum + tailNum;

  for(int i = 0; i < threadNum; ++i) {
    results.push_back(pull.addTask([this, initPoint, endPoint](){partProcess(initPoint, endPoint);}));
    initPoint = endPoint;
    endPoint += blockNum;
  }

  // Тут нужно дождать выполнения задач, не потоков
  for(auto& taskReturn: results){
    taskReturn.get();
  }

  results.clear();

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

