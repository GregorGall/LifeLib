#include <Engines/OpenMPEngine.h>

Life::OpenMPEngine::OpenMPEngine(Desk &desk): LifeEngine(desk)
{
}

void Life::OpenMPEngine::process()
{
  calculate();
  evolute();
}

void Life::OpenMPEngine::calculate()
{
  #pragma omp parallel for if(desk.size() > 1000) num_threads(omp_get_max_threads()/2)
  for(int i = 0; i < desk.size(); ++i) {
      auto& cell = desk[i];
      if(cell) {
        for(auto neighbour: desk.getNeighbours(&cell)) {
          neighbour->increment();
        }
      }
  }
}

void Life::OpenMPEngine::evolute()
{
  #pragma omp parallel for if(desk.size() > 1000) num_threads(omp_get_max_threads()/2)
  for(int i = 0; i < desk.size(); ++i) {
      desk[i].evolute();
  }
}

