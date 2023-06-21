#include "LifeModel.h"

/*!
 * \details
 * Конструктор инициализирует игровое поле переданными значениями и устанавливает не многопоточный движок
 * по умолчанию. Межкадровая дополнительная задержка по умолчанию 0.
 */
Life::LifeModel::LifeModel(int rows, int cols): desk(rows, cols)
{
  setEngine(Life::EngineType::common);
}

/*!
 * \details
 * Константная ссылка на игровое поле обеспечивает чтение текущего состояния пользователем
 */
const Life::Desk &Life::LifeModel::readData() const
{
  return desk;
}

/*!
 * \details
 * Чтение текущей дополнительной межкадровой задержки
 */
const std::chrono::milliseconds& Life::LifeModel::readDelay() const
{
  return delay;
}

/*!
 * \details
 * Установка дополнительной межкадровой задержки в мс
 */
void Life::LifeModel::setDelay(std::chrono::milliseconds input)
{
  if(input.count() >= 0) {
      delay = input;
  }
}

/*!
 * \details
 * Изменение размеров игрового поля.
 */
void Life::LifeModel::resize(int rows, int cols)
{
  desk.resize(rows, cols);

  // Реинициализация информации о клетках на доске т.к. при resize перевыделяется память
  engine->reset();
}

/*!
 * \details
 * Очистка. Для движка вызывается повторная инициализация (сброс).
 */
void Life::LifeModel::clearDesk()
{
  std::lock_guard gaurd(dataMutex);
  desk.clear();

  // Реинициализация информации о клетках на доске т.к. клетки очищаются не через движок
  engine->reset();
}

/*!
 * \details
 * Переключение состояния клетки
 */
void Life::LifeModel::toggleCell(int row, int col)
{
  engine->toggleCell(row, col);
}

/*!
 * \details
 * Установка типа движка. Макросы USE_* реализуют механизм условной компиляции не добавляя конструкторы
 * движков сборка которых невозможна.
 */
void Life::LifeModel::setEngine(EngineType type)
{
  std::lock_guard gaurd(dataMutex);
  switch (type) {
    case EngineType::common:
      engine = std::make_unique<CommonEngine>(desk);
      break;
    case EngineType::thread:
      USE_THREAD(engine = std::make_unique<ThreadEngine>(desk);)
      break;
    case EngineType::openmp:
      USE_OPENMP(engine = std::make_unique<OpenMPEngine>(desk);)
      break;
    case EngineType::cuda:
      USE_CUDA()
      break;
    default:
      engine = std::make_unique<CommonEngine>(desk);
  }
}

/*!
 * \details
 * Запуск петли расчета новых поколений. Расчет продолжается до переключения флага proceed в состояние False
 * (вызывается методов stop). В аргументах передается callBack функция которая может использовать для уведомления
 * о завершении расчета очередного кадра, счетчика и т.п.
 */
void Life::LifeModel::run(std::function<void()> callBack)
{
  while(proceed) {
    std::this_thread::sleep_for(delay);
    std::lock_guard gaurd(dataMutex);
    engine->process();
    if(callBack){ callBack(); }
  }

  proceed = true;
}
