#include <Engines/CommonEngine.h>

/*!
 * \details
 * В конструкторе инициализируется ссылка на объект поля и
 * заполняется информация о живых клетках
 */
Life::CommonEngine::CommonEngine(Desk& desk): LifeEngine(desk)
{
  init();
}

/*!
 * \details
 * При сбросе движка требуется !очистить! и заново заполнить информацию о живых клетках
 */
void Life::CommonEngine::reset()
{
  aliveCells.clear();
  init();
}

/*!
 * \details
 * Инициализация - заполнение информации о живых клетках
 */
void Life::CommonEngine::init()
{
  for(int i = 0; i < desk.size(); ++i) {
    if(desk[i]){ aliveCells.insert(&desk[i]); }
  }
}

/*!
 * \details
 */
void Life::CommonEngine::add(Cell *cell)
{
  aliveCells.insert(cell);
}

/*!
 * \details
 */
void Life::CommonEngine::remove(Cell *cell)
{
  aliveCells.erase(cell);
}

/*!
 * \details
 * Для этой версии движка требуется поддерживать в актуальном состоянии
 * информацию о живых клетках, поэтому используются дополнительные функции
 * add и remove.
 */
void Life::CommonEngine::toggleCell(int row, int col)
{
  auto& cell = desk(row, col);
  cell.toggle() ? add(&cell) : remove(&cell);
}

/*!
 * \details
 * Последовательный расчет числа соседей и переключение состояния
 */
void Life::CommonEngine::process()
{
  evolute(calculate());
}

/*!
 * \details
 *  Цикл по контейнеру с живыми клетками. Для каждой клетки получается список соседей и
 *  каждый из соседей инкрементируется на единицу. Метод возвращает контейнер с указателями
 *  на инкрементированные клетки, требующие обработки.
 */
auto Life::CommonEngine::calculate() -> CellSet
{
  CellSet cellsToEvolute;

  for(auto& cell: aliveCells) {
    for(auto& neighbour: desk.getNeighbours(cell)) {
      neighbour->increment();
      cellsToEvolute.insert(neighbour);
    }

    cellsToEvolute.insert(cell);
  }

  return cellsToEvolute;
}

/*!
 * \details
 *  Цикл по клеткам требующим обработки, если клетка становится живой, то добавляется в список
 *  живых.
 */
void Life::CommonEngine::evolute(CellSet&& cellSet)
{
  aliveCells.clear();
  for(auto cell: cellSet) {
    cell->evolute();
    if(*cell) { add(cell); }
  }
}
