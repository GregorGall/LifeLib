#pragma once
#include <mutex>
#include <condition_variable>

/*!
 *  \file
 *  \brief Описание класса синхронизации потоков
 */

namespace Life {

/*!
 * \brief Класс синхронизации потоков
 *
 * Инициализируется числом потоков для синхронизации. Вызов метода wait блокирует выполненение потока, пока
 * до этого метода не дойдет указанное количество остальных.
 */
  class barrier {

  public:

      /*! Конструктор */
      barrier(){}

      /*! Метод ожидания
       *
       *  \details
       *  Если число зашедших потоков в метод не равно числу для синхронизации, то новый поток блокируется.
       *  В противном случае через condition_variable разблокируются все пришедшие потоки.
       */
      void wait()
      {
          std::unique_lock lk(syncMutex);
          if(threadNum <= syncThread){
              syncThread = 0;
          }

          ++syncThread;

          // C CondVar требуется использовать while как защиту от spurious wakeup
          while(threadNum > syncThread){
              syncVar.wait(lk);
          }

          wakeUp();
      }

      /*! Установка количества синхронизируемых потоков  */
      void reset(int threadToSync) { threadNum = threadToSync; }

  private:

      /*! Пробуждение всех потоков */
      void wakeUp()
      {
          syncVar.notify_all();
      }

  private:

      /*! Число зашедших потоков */
      unsigned int threadNum{ 1 };

      /*! Число синхронизируемых потоков */
      unsigned int syncThread{ 0 };

      /*! Мьютекс синхронизации */
      std::mutex syncMutex;

      /*! Переменная синхронизации */
      std::condition_variable syncVar;

  };

}
