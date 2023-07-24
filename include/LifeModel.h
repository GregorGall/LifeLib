#pragma once
#include <memory>
#include <thread>
#include <mutex>
#include <chrono>
#include <functional>

#include "CommonEngine.h"

#ifndef NO_OPENMP
  #include "OpenMPEngine.h"
#endif

#ifndef NO_THREAD
  #include "ThreadEngine/ThreadEngine.h"
#endif

/*!
 *  \file
 *  \brief Класс - модель игры Жизнь
 */

/*! Основное пространство имен библиотеки */
namespace Life {

  /*! Типы движков */
  enum class EngineType {
    common,               ///< Движок по умолчанию - не многопоточный
    thread,               ///< Движок основанный на std::thread
    openmp,               ///< Движок с поддержкой библиотеки OpenMP
    cuda                  ///< Движок с поддержкой библиотеки CUDA Toolkit
  };

  /*!
   * \brief Класс клеточного автомата
   *
   * Используется для представления отдельных ячеек на поле и их состояния
   */
  class LifeModel {

  public:

    /*! Конструктор */
    explicit LifeModel(int rows = 0, int cols = 0);

    /*! Метод доступа к состоянию поля */
    const Desk& readData() const;

    /*! Метод чтения текущей установленной задержки между кадрами */
    const std::chrono::milliseconds& readDelay() const;

    /*! Запуск петли расчета поколений */
    void run(std::function<void()> callBack = nullptr);

    /*! Остановка расчета */
    void stop(){ proceed = false; }

    /*! Переключить состояние клетки */
    void toggleCell(int row, int col);

    /*! Метод установки движка */
    void setEngine(EngineType type);

    /*! Метод установки дополнительной задержки между кадрами */
    void setDelay(std::chrono::milliseconds input);

    /*! Изменение размеров игрового поля */
    void resize(int rows, int cols);

    /*! Очистка игрового поля */
    void clearDesk();

    /*! Потокобезопасное переключени группы клеток - добавление фигуры */
    template<class container>
    void toggleGroup(const container& cellGroup )
    {
      std::lock_guard gaurd(dataMutex);
      for(auto& cell: cellGroup) {
        toggleCell(cell.first, cell.second);
      }
    }

  private:

    /*! Игровое поле */
    Desk desk;

    /*! Защита данных при расчете, очистке и переключении клеток на поле */
    std::mutex dataMutex;

    /*! Указатель на движок */
    std::unique_ptr<LifeEngine> engine{ nullptr };

    /*! Дополнительная задержка между кадрами */
    std::chrono::milliseconds delay{ 0 };

    /*! Флаг продолжения расчетов True -> продолжаем, False -> завершаем */
    bool proceed{ true };

  };

}
