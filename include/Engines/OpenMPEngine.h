#pragma once
#include <omp.h>
#include <unordered_set>

#include "LifeEngine.h"

/*!
 *  \file
 *  \brief Многопоточный движок
 */

namespace Life {

/*!
 * \brief Класс движка реализующего многопоточный расчет
 *
 * Для ускорения вычислений используются директивы библиотеки OpenMP
 */
  class OpenMPEngine: public LifeEngine {

  public:

    /*! Конструктор */
    OpenMPEngine(Desk& desk);

    /*! Метод расчета нового поколения */
    void process() override final;

  private:

    /*! Подсчет числа соседей */
    void calculate();

    /*! Переключение состояния */
    void evolute();

  };

}
