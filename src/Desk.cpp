#include "Desk.h"

Life::Desk::Desk(int rows, int cols): m_rows{rows}, m_cols{cols}
{
  data = std::make_unique<Cell[]>(size());
}

Life::Cell &Life::Desk::operator[](int index)
{
  return data[index];
}

Life::Cell& Life::Desk::operator()(int row, int col)
{
  return const_cast<Cell&>(
        static_cast<const Desk&>(*this).operator()(row, col)
  );
}

const Life::Cell& Life::Desk::operator()(int row, int col) const
{
  return data[row*m_cols + col];
}

void Life::Desk::clear()
{
  for(int i = 0; i < size(); ++i) {
    data[i].kill();
  }
}

void Life::Desk::resize(int rows, int cols)
{
  data = std::make_unique<Cell[]>(rows*cols);
  m_rows = rows;
  m_cols = cols;
}

std::list<Life::Cell*> Life::Desk::getNeighbours(Cell* cell)
{
  int length = cell - data.get();
  return getNeighbours(length / m_cols, length % m_cols);
}

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

