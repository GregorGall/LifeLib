#pragma once

#include "Desk.h"
#include "Cell.h"

/*!
 *  \file
 *  \brief Описание интерфейса движка
 */

/*! Макрос отключения OpenMP
 *  \details
 *  Отключает выражение в скобках (expr) при наличии определения компиляции NO_OPENMP.
 *  Используется для отключения компиляции движка с OpenMP в случае, если не найдена библиотека OpenMP
 */
#ifdef NO_OPENMP
  #define USE_OPENMP(expr)
#else
  #define USE_OPENMP(expr) expr
#endif

/*! Макрос отключения Thread
 *  \details
 *  Отключает выражение в скобках (expr) при наличии определения компиляции NO_THREAD.
 *  Используется для отключения компиляции движка на std::thread.
 */
#ifdef NO_THREAD
  #define USE_THREAD(expr)
#else
  #define USE_THREAD(expr) expr
#endif

/*! Макрос отключения Cuda
 *  \details
 *  Отключает выражение в скобках (expr) при наличии определения компиляции NO_CUDA.
 *  Используется для отключения компиляции движка с Cuda в случае, если не найдена библиотека Cuda.
 */
#ifdef NO_CUDA
  #define USE_CUDA(expr)
#else
  #define USE_CUDA(expr) expr
#endif

namespace Life {

  /*!
   * \brief Абстрактный класс движка
   *
   * Используется для реализации специфических классов обработки нового поколения клеток
   */
  class LifeEngine {

  public:

    /*! Конструктор */
    LifeEngine(Desk& desk);

    /*! Деструктор */
    virtual ~LifeEngine() = default;

    /*! Метод установки начального состояния */
    virtual void reset();

    /*! Метод расчета нового поколения */
    virtual void process() = 0;

    /*! Метод переключения состояния клетки (жива/мертва) */
    virtual void toggleCell(int row, int col);

  protected:

    /*! Ссылка на объект игрового поля */
    Desk& desk;

  };

}
