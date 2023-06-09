#include <Engines/CommonEngine.h>

Life::CommonEngine::CommonEngine(Desk& desk): LifeEngine(desk)
{
  for(int i = 0; i < desk.size(); ++i) {
    if(desk[i]){ aliveCells.insert(&desk[i]); }
  }
}

void Life::CommonEngine::toggleCell(int row, int col)
{
  auto& cell = desk(row, col);
  cell.toggle() ? add(&cell) : remove(&cell);
}

auto Life::CommonEngine::calculate() -> CellSet
{
  CellSet cellsToEvolute;

  for(auto cell: aliveCells) {
    for(auto& neighbour: desk.getNeighbours(cell)) {
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
  for(auto cell: cellSet) {
    cell->evolute();
    if(*cell) { add(cell); }
  }
}
