#include <Engines/OpenMPEngine.h>

/*!
 * \details
 * В конструкторе инициализируется ссылка на объект поля.
 */
Life::OpenMPEngine::OpenMPEngine(Desk &desk): LifeEngine(desk)
{
}

/*!
 * \details
 * Последовательный расчет числа соседей и переключение состояния. Расчет ведется по всему
 * полю.
 */
void Life::OpenMPEngine::process()
{
  calculate();
  evolute();
}

/*!
 * \details
 * Для каждой клетки поля инкрементируются на единицу все ее соседи. Распараллеливание цикла
 * проводится только при размерах поля выше 1000 клеток.
 */
void Life::OpenMPEngine::calculate()
{
  #pragma omp parallel for if(desk.size() > 1000) num_threads(omp_get_max_threads())
  for(int i = 0; i < desk.size(); ++i) {
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
 * Для каждой клетки выполняется обработка состояния. Распараллеливание цикла
 * проводится только при размерах поля выше 1000 клеток.
 */
void Life::OpenMPEngine::evolute()
{
  #pragma omp parallel for if(desk.size() > 1000) num_threads(omp_get_max_threads())
  for(int i = 0; i < desk.size(); ++i) {
      desk[i].evolute();
  }
}

