#pragma once
#include <vector>
#include <thread>

/*!
 *  \file
 *  \brief Описание класса присоединения вектора потоков
 */

namespace Life {

/*!
 * \brief Класс присоединения вектора потоков
 *
 * Хранит ссылку на вектор потоков и вызывает метод join для каждого из них
 * при уничтожении собственного экземпляра.
 */
  class thrJoiner {

  public:

    /*! Конструктор
     *
     *  \details
     *  Выполняет инициализацию ссылки на вектор потоков.
     */
    explicit thrJoiner(std::vector<std::thread>& threads): threads_(threads)
    {
    }

    /*! Деструктор
     *
     *  \details
     *  Вызывает методы join для каждого потока в векторе, если это возможно.
     */
    ~thrJoiner()
    {
      for(unsigned long i = 0; i < threads_.size(); ++i){
        if(threads_[i].joinable()){
          threads_[i].join();
        }
      }
    }

  private:

    /*! Ссылка на вектор потоков */
    std::vector<std::thread>& threads_;

  };

}
