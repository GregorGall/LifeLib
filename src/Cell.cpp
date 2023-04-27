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
  if( neighbours != minimumNeighboursToLive) {
    status = (neighbours == lifeThreshold);
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
