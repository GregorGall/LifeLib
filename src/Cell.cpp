#include "Cell.h"

void Life::Cell::kill()
{
  status = false;
}

void Life::Cell::renew()
{
  status = true;
}

bool Life::Cell::toggle()
{
  return status = !status;
}

void Life::Cell::evolute()
{
  if( neighbours != 2) {
    status = (neighbours == 3);
  }

  neighbours = 0;
}

void Life::Cell::increment()
{
  ++neighbours;
}

Life::Cell::operator bool() const
{
  return status;
}
