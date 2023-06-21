#pragma once
#include <atomic>

/*!
 *  \file
 *  \brief Описание класса "Клетки"
 */

namespace Life {

  /*! Пороговое количество для оживания и максимальное до перенаселения */
  const int lifeThreshold = 3;

  /*! Минимальное количество для продолжения жизни */
  const int minimumNeighboursToLive = 2;

  /*!
   * \brief Класс клеточного автомата
   *
   * Используется для представления отдельных ячеек на поле и их состояния
   */
  class Cell {

  public:

    /*! Убийство клетки */
    void kill();

    /*! Возрождение клетки */
    void renew();

    /*! Переключение текущего состояния клетки */
    bool toggle();

    /*! Расчет нового состояния */
    void evolute();

    /*! Инкремент счетчика живых соседей */
    void increment();

    /*! Оператор преобразования к bool */
    explicit operator bool() const;

  private:

    /*! Текущее состояние клетки: жива/мертва (true/false) */
    bool status{ false };

    /*! Счетчик живых соседей (Атомик необходим для потокобезопасного инкремента) */
    std::atomic_int neighbours{ 0 };

  };

}
