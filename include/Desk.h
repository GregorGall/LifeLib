#pragma once
#include <memory>
#include <list>

#include "Cell.h"

namespace Life {

  class Desk {

  public:

    Desk(int rows, int cols);

    Desk(const Desk& other);

    ~Desk(){}

    Desk& operator=(const Desk& other);

    Cell& operator()(int row, int col);

    const Cell& operator()(int row, int col) const;

    void resize(int rows, int cols);

    std::list<Cell*> getNeighbours(Cell*);

    std::list<Cell*> getNeighbours(int row, int col);

    int rows() const { return m_rows; }
    int cols() const { return m_cols; }
    int size() const { return m_rows*m_cols; }

  private:

    int m_rows{ 0 };
    int m_cols{ 0 };
    std::unique_ptr<Cell[]> data;

  };

}
