#include <Engines/CommonEngine.h>

auto Life::CommonEngine::calculate() -> CellSet
{
  CellSet cellsToEvolute;

  for(auto cell: aliveCells) {

    auto neighbourList = desk.getNeighbours(cell);

    for(auto& neighbour: neighbourList){
      neighbour->increment();
      cellsToEvolute.insert(neighbour);
    }

    cellsToEvolute.insert(cell);
  }

  return cellsToEvolute;
}

void Life::CommonEngine::evolute(CellSet cellSet)
{
  aliveCells.clear();
  for(auto cell: cellSet){
    cell->evolute();
    if(*cell){ aliveCells.insert(cell); }
  }
}
