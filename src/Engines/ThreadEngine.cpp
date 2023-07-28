#include <Engines/ThreadEngine/ThreadEngine.h>

/*!
 * \details
 * В конструкторе инициализируется ссылка на объект поля и указывается
 * число потоков для точки синхронизации.
 */
Life::ThreadEngine::ThreadEngine(Desk &desk): LifeEngine(desk)
{
  syncPoint.reset(pull.size());
}

/*!
 * \details
 * Метод создает и распределяет задачи по расчету в пул исходя из
 * доступного числа потоков.
 */
void Life::ThreadEngine::process()
{
  int threadNum = pull.size();
  int tailNum = desk.size() % threadNum;
  int blockNum = desk.size() / threadNum;

  int initPoint = 0;
  int endPoint = blockNum + tailNum;

  // Создаем задачи
  for(int i = 0; i < threadNum; ++i) {
    results.push_back(pull.addTask( [this, initPoint, endPoint](){partProcess(initPoint, endPoint);}  ));
    initPoint = endPoint;
    endPoint += blockNum;
  }

  // Ожидаем завершения запущенных задач
  for(auto& taskReturn: results){
    taskReturn.get();
  }

  results.clear();
}

/*!
 * \details
 */
void Life::ThreadEngine::partProcess(int initPoint, int endPoint)
{
  calculate(initPoint, endPoint);
  syncPoint.wait();
  evolute(initPoint,endPoint);
}

/*!
 * \details
 */
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

/*!
 * \details
 */
void Life::ThreadEngine::evolute(int initPoint, int endPoint)
{
  for(int i = initPoint; i < endPoint; ++i) {
      desk[i].evolute();
  }
}

