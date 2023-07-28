#pragma once
#include <list>
#include <functional>

/*!
 *  \file
 *  \brief Методы создания фигур
 */

namespace Life {

  /*! Тип группы ячеек описывающих фигуру */
  using cellGroup = std::list<std::pair<int, int>>;

  /*! Тип функции создания фигуры */
  using makeFnc = std::function<cellGroup(int,int)>;

  /*! Глайдер */
  cellGroup makeGlider(int row, int col);

  /*! Вретикальный стик (***) */
  cellGroup makeStick(int row, int col);

  /*! Пруд */
  cellGroup makePond(int row, int col);

  /*! Квадрат */
  cellGroup makeSquare(int row, int col);

  /*! Жаба */
  cellGroup makeToad(int row, int col);

  /*! Корабль */
  cellGroup makeBoat(int row, int col);

}
