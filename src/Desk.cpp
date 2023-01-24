#include "Desk.h"

Life::Desk::Desk(int rows, int cols): m_rows{rows}, m_cols{cols}
{
  data = std::make_unique<Cell[]>(size());
};

Life::Desk::Desk(const Desk& other): m_rows{other.m_rows}, m_cols{other.m_cols}
{
  data = std::make_unique<Cell[]>(size());
  for(int i = 0; i < size(); ++i){
    data[i] = other.data[i];
  }
}

Life::Desk& Life::Desk::operator=(const Desk& other)
{
  if(this == &other){ return *this; }

  data = std::make_unique<Cell[]>(size());
  for(int i = 0; i < size(); ++i){
    data[i] = other.data[i];
  }

  m_rows = other.m_rows;
  m_cols = other.m_cols;
  return *this;
}

const Life::Cell& Life::Desk::operator()(int row, int col) const
{
  return data[row*m_cols + col];
};

Life::Cell& Life::Desk::operator()(int row, int col)
{
  return const_cast<Cell&>(
        static_cast<const Desk&>(*this).operator()(row, col)
  );
};

void Life::Desk::resize(int rows, int cols)
{
  data = std::make_unique<Cell[]>(rows*cols);
  m_rows = rows;
  m_cols = cols;
}

std::list<Life::Cell*> Life::Desk::getNeighbours(int row, int col){

  // Если центральная клетка на границе, то соседняя клетка у другого края
  int decRow = ( row == 0 ) ? m_rows : row - 1;
  int decCol = ( col == 0 ) ? m_cols : col - 1;

  int incRow = ( row == m_rows ) ? 0 : row + 1;
  int incCol = ( col == m_cols ) ? 0 : col + 1;

  std::list<Cell*> tmp{           // У клетки в матрице 8 соседей
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

