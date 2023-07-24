#include <benchmark/benchmark.h>
#include "LifeModel.h"
#include "Figures.h"

const int figureHeight = 3;
const int figureWidth = 3;
const int figureSpace = 1;

void toggleSwarm(Life::LifeEngine& engine, int figureRowNum, int figureColNum)
{

  for(int i = 0; i < figureRowNum; ++i){
    for(int j = 0; j < figureColNum; ++j){

      for(auto& cell: Life::makeStick(1+i*(figureHeight + figureSpace), 1+j*(figureWidth + figureSpace))) {
        engine.toggleCell(cell.first, cell.second);
      }

    }
  }
}

const int rows = 1024;
const int cols = 1024;
constexpr int maxFigureInRow = rows/(figureHeight + figureSpace);
constexpr int maxFigureInCol = cols/(figureWidth + figureSpace);

template<typename LifeEngine>
void LifeEngine_FillBM(benchmark::State& state){

  Life::Desk desk(rows, cols);
  LifeEngine engine(desk);
  toggleSwarm(engine, state.range(0), state.range(0));

  for(auto _ : state)
    engine.process();

}

BENCHMARK(LifeEngine_FillBM<Life::CommonEngine>)->RangeMultiplier(4)->Range(1, maxFigureInRow)->Unit(benchmark::kMillisecond)->Name("Common")->UseRealTime();
BENCHMARK(LifeEngine_FillBM<Life::OpenMPEngine>)->RangeMultiplier(4)->Range(1, maxFigureInRow)->Unit(benchmark::kMillisecond)->Name("OpenMp")->UseRealTime();
BENCHMARK(LifeEngine_FillBM<Life::ThreadEngine>)->RangeMultiplier(4)->Range(1, maxFigureInRow)->Unit(benchmark::kMillisecond)->Name("Thread")->UseRealTime();
