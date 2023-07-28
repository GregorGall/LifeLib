#pragma once
#include <unordered_set>

#include "LifeEngine.h"

/*!
 *  \file
 *  \brief Однопоточный движок
 */

namespace Life {

  /*!
   * \brief Класс движка реализующего однопоточный расчет
   *
   * На протяжении работы поддерживается актуальный список живых клеток. Для генерации очередного
   * кадра расчитывается только область вокруг таких клеток.
   */
  class CommonEngine: public LifeEngine {

    /*! Тип хранения для живых клеток  */
    using CellSet = std::unordered_set<Cell*>;

  public:

    /*! Конструктор */
    CommonEngine(Desk& desk);

    /*! Добавить клетку в список живых */
    void add(Cell* cell);

    /*! Удалить клетку из списка живых */
    void remove(Cell* cell);

    /*! Реинициализация */
    void reset() override final;

    /*! Метод расчета нового поколения */
    void process() override final;

    /*! Метод переключения состояния клетки (жива/мертва) */
    void toggleCell(int row, int col) override final;

  private:

    /*! Живые клетки на поле */
    CellSet aliveCells;

  private:

    /*! Инициализация движка */
    void init();

    /*! Подсчет числа соседей */
    CellSet calculate();

    /*! Переключение состояния */
    void evolute(CellSet&& cellSet);

  };

}
