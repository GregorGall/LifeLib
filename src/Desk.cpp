#include "Desk.h"

/*!
 * \details
 * Инициализация размеров и выделение памяти
 */
Life::Desk::Desk(int rows, int cols): m_rows{rows}, m_cols{cols}
{
  data = std::make_unique<Cell[]>(size());
}

/*!
 * \details
 * Просто линейный доступ по индексу
 */
Life::Cell &Life::Desk::operator[](int index)
{
  return data[index];
}

/*!
 * \details
 * Доступ по константной ссылке по координатам
 */
const Life::Cell& Life::Desk::operator()(int row, int col) const
{
  return data[row*m_cols + col];
}

/*!
 * \details
 * Доступ по ссылке по координатам. Хотя обычно const_cast не является безопасным поведением
 * в данном случае его использование возможно, т.к. вызов неконстантного метода и так подразумевает
 * изменение ресурса. (Скотт Мэйерс 55 советов)
 */
Life::Cell& Life::Desk::operator()(int row, int col)
{
  return const_cast<Cell&>(
        static_cast<const Desk&>(*this).operator()(row, col)
  );
}

/*!
 * \details
 * Перевод всех клеток в неживое состояние
 */
void Life::Desk::clear()
{
  for(int i = 0; i < size(); ++i) {
    data[i].kill();
  }
}

/*!
 * \details
 * Изменение размеров поля выполняется с перевыделением памяти
 */
void Life::Desk::resize(int rows, int cols)
{
  data = std::make_unique<Cell[]>(rows*cols);
  m_rows = rows;
  m_cols = cols;
}

/*!
 * \details
 * Перегрузка метода получения списка соседей для доступа по указателю.
 * Т.к. матрица в памяти хранится построчно, то можно рассчитать сдвиг.
 */
std::list<Life::Cell*> Life::Desk::getNeighbours(Cell* cell)
{
  int length = cell - data.get();
  return getNeighbours(length / m_cols, length % m_cols);
}

/*!
 * \details
 * Метод получения списка всех соседей клетки с координатами row, col
 */
std::list<Life::Cell*> Life::Desk::getNeighbours(int row, int col)
{

  // Если центральная клетка на границе, то соседняя клетка у другого края
  int decRow = ( row == 0 ) ? m_rows - 1 : row - 1;
  int decCol = ( col == 0 ) ? m_cols - 1 : col - 1;

  int incRow = ( row == m_rows - 1 ) ? 0 : row + 1;
  int incCol = ( col == m_cols - 1 ) ? 0 : col + 1;

  std::list<Cell*> tmp {          // У клетки в матрице 8 соседей
    &operator()(decRow, decCol),  //
    &operator()(row   , decCol),  //  * * *
    &operator()(incRow, decCol),  //  * + *
    &operator()(decRow, col   ),  //  * * *
    &operator()(incRow, col   ),
    &operator()(decRow, incCol),
    &operator()(row   , incCol),
    &operator()(incRow, incCol)
  };

  return tmp;
}

