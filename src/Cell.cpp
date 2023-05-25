#include "Cell.h"

void Life::Cell::kill()
{
  status = false;
  neighbours.store(0);
}

void Life::Cell::renew()
{
  status = true;
}

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
  // Если число соседей == минимуму для продолжения  жизни, то ничего делать не надо. Живое живет, мертвое мертво
  if( neighbours != minimumNeighboursToLive) {
    // Если соседей меньше минимума или больше порога, клетка умирает, если равно, то живет или оживает
    status = (neighbours == lifeThreshold);
  }

  neighbours.store(0);
}

void Life::Cell::increment()
{
  ++neighbours;
}

Life::Cell::operator bool() const
{
  return status;
}
