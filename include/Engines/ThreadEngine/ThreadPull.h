#pragma once
#include <deque>
#include <atomic>
#include <mutex>
#include <exception>
#include <vector>
#include <thread>
#include <future>
#include <functional>

#include "thrJoiner.h"

/*!
 *  \file
 *  \brief Описание класса пул потоков
 */

namespace Life {

/*!
 * \brief Пул потоков с ожиданием завершения задач
 *
 * Хранит вектор потоков исполняющих цикл по ожиданию и запуску задач.
 * Особенность реализации в возврате future при добавлении задачи, что позволяет
 * дожидаться ее завершения.
 */
  class ThreadPull {

  public:

    /*! Конструктор */
    ThreadPull();

    /*! Деструктор */
    ~ThreadPull();

    /*! Количество потоков в пуле */
    size_t size();

    /*! Шаблон добавления задачи */
    template<typename T>
    std::future<void> addTask(T f){

      std::packaged_task<task_t> pt(f);
      auto future = pt.get_future();

      std::lock_guard lk(taskMutex);
      taskQueue.push_back(std::move(pt));
      return future;
    }

  private:

    /*! Метод по ожиданию и запуску выполняемый в потоке */
    void exec();

  private:

    /*! Тип принимаемой задачи */
    using task_t = void();

    /*! Мьютекс для безопасного доступа к очереди задачи */
    std::mutex taskMutex;

    /*! Флаг необходимости завершения потоков */
    std::atomic_bool done;

    /*! Очередь задач на выполнение */
    std::deque<std::packaged_task<task_t>> taskQueue;

    /*! Вектор потоков */
    std::vector<std::thread> threads;

    /*! Объект ожидания завершения вектора потоков
     *
     *  \details
     *  По истечению времени жизни пула потоков первым уничтожается именно этот объект
     *  (поэтому важен порядок расположения членов) в его деструкторе вызывается join для каждого потока
     *  из вектора. Флаг done выставленный в значение true останавливает цикл и позволяет
     *  завершиться методу exec. Объект удобен т.к. при провале запуска какого-либо потока и выбрасывании исключения нужно
     *  дождаться завершения уже запущенных экзампляров.
     *
     *  \todo
     *  Более практичным было бы использование jthreads, но нужна свежая версия компилятора.
     */
    thrJoiner joiner;

  };


}
