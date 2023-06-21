#include "Cell.h"

/*!
 * \details
 * Переключает клетку в состояние false и обнуляет число ее живых соседей.
 * Обнуление соседей нужно для отсутствия спонтанного возраждения при вызове evolute.
 */
void Life::Cell::kill()
{
  status = false;
  neighbours.store(0);
}

/*!
 * \details
 * Переключает клетку в состояние true
 */
void Life::Cell::renew()
{
  status = true;
}

/*!
 * \details
 * Переключает текущее состояние и возвращает результат
 */
bool Life::Cell::toggle()
{
  return status = !status;
}


/*!
  \details
  Правила Life:
  * В пустой клетке, которая соседствует с тремя живыми, зарождается жизнь.
  * Если у живой клетки две или три живые соседки, то она продолжает жить. В противном случае умирает.
*/
void Life::Cell::evolute()
{
  // Если число соседей == минимуму для продолжения  жизни, то ничего делать не надо. Живое - живет, мертвое - мертво, иначе:
  if( neighbours != minimumNeighboursToLive) {
    // Если соседей меньше минимума или больше порога, клетка умирает, если равно, то живет или оживает
    status = (neighbours == lifeThreshold);
  }

  neighbours.store(0);
}

/*!
 * \details
 * Потокобезопасный инкремент числа соседей
 */
void Life::Cell::increment()
{
  ++neighbours;
}

/*!
 * \details
 * Для if и некоторых других случаев преобразование к bool объявленное как explicit не требует явного каста
 */
Life::Cell::operator bool() const
{
  return status;
}
