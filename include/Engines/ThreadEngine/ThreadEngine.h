#pragma once
#include <memory>
#include <thread>
#include <vector>

#include "barrier.h"
#include "ThreadPull.h"
#include "LifeEngine.h"

/*!
 *  \file
 *  \brief Многопоточный движок
 */

namespace Life {

/*!
 * \brief Класс движка реализующего многопоточный расчет
 *
 * Для ускорения вычислений используется пул потоков std::thread, что позволяет один
 * раз инициализировать объекты потоков и в дальнейшем лишь передавать им новые задачи.
 */
  class ThreadEngine: public LifeEngine {

  public:

    /*! Конструктор */
    ThreadEngine(Desk& desk);

    /*! Метод расчета нового поколения */
    void process() override final;

  private:

    /*! Метод расчета нового поколения для части поля */
    void partProcess(int initPoint, int endPoint);

    /*! Подсчет числа соседей для части поля */
    void calculate(int initPoint, int endPoint);

    /*! Переключение состояния для части поля */
    void evolute(int initPoint, int endPoint);

  private:

    /*! Вектор результатов выполнения задач переданных потокам
     *
     * \details
     * Т.к. пул потоков создается один раз и уничтожается только по завершению
     * программ, в методе process требуется ожидать завершения задач, а не потоков.
     * Переменная results хранит объекты future возвращаемые пулом потоков при добавлении
     * в него задачи (lambda оборачивается в packaged_task), которые и позволяют дождаться ее
     * завершения.
     */
    std::vector<std::future<void>> results;

    /*! Точка синхронизации
     *
     *  \details
     *  Переключение состояний клеток возможно только после подсчета соседей
     *  на всем поле, поэтому необходимо дождаться выполнения всеми потоками метода
     *  calculate, прежде чем начинать evolute.
     */
    barrier syncPoint;

    /*! Пул потоков */
    ThreadPull pull;

  };

}
