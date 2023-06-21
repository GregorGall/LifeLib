#pragma once
#include <memory>
#include <list>

#include "Cell.h"

/*!
 *  \file
 *  \brief Описание класса "Игровое поле"
 */

namespace Life {

  /*!
   * \brief Класс игровое поле
   *
   * Используется для хранения ячеек и удобного доступа к списку соседей
   */
  class Desk {

  public:

    /*! Конструктор */
    explicit Desk(int rows, int cols);

    /*! Оператор линейного доступа */
    Cell& operator[](int index);

    /*! Оператор доступа по координатам */
    Cell& operator()(int row, int col);

    /*! Константный оператор доступа по координатам */
    const Cell& operator()(int row, int col) const;

    /*! Доступ к списку соседей */
    std::list<Cell*> getNeighbours(Cell*);

    /*! Доступ к списку соседей */
    std::list<Cell*> getNeighbours(int row, int col);

    /*! Очистка поля от живых клеток */
    void clear();

    /*! Изменение размеров поля */
    void resize(int rows, int cols);

    /*! Список строк */
    int rows() const { return m_rows; }

    /*! Список колонок */
    int cols() const { return m_cols; }

    /*! Общий размер */
    int size() const { return m_rows*m_cols; }

  private:

    /*! Число строк */
    int m_rows{ 0 };

    /*! Число колонок */
    int m_cols{ 0 };

    /*! Динамический массив данных
     *  \details
     *  Использование вектора потребует явной реализации конструктора копирования для Cell из-за atomic
     */
    std::unique_ptr<Cell[]> data{ nullptr };

  };

}
