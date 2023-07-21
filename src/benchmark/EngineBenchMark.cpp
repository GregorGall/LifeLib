#include <benchmark/benchmark.h>
#include "LifeModel.h"

const int rows = 1024;
const int cols = 1024;
const int figureHeight = 3;
const int figureWidth = 3;
const int figureSpace = 1;
constexpr int maxFigureInRow = rows/(figureHeight + figureSpace);
constexpr int maxFigureInCol = cols/(figureWidth + figureSpace);

using cellGroup = std::list<std::pair<int, int>>;
using makeFnc = std::function<cellGroup(int,int)>;

cellGroup makeStick(int row, int col) {
  return { {row,     col},
           {row + 1, col},
           {row + 2, col} };
}

void toggleGroup(Life::LifeEngine& engine, int figureRowNum, int figureColNum)
{

  for(int i = 0; i < figureRowNum; ++i){
    for(int j = 0; j < figureColNum; ++j){

      for(auto& cell: makeStick(1+i*(figureHeight + figureSpace), 1+j*(figureWidth + figureSpace))) {
        engine.toggleCell(cell.first, cell.second);
      }

    }
  }
}

template<typename LifeEngine>
void BM_LifeEngine(benchmark::State& state){

  Life::Desk desk(cols, rows);
  LifeEngine engine(desk);
  toggleGroup(engine, state.range(0), state.range(0));

  for(auto _ : state)
    engine.process();

}

BENCHMARK(BM_LifeEngine<Life::CommonEngine>)->RangeMultiplier(4)->Range(1, maxFigureInRow)->Unit(benchmark::kMillisecond)->Name("Common")->UseRealTime();
BENCHMARK(BM_LifeEngine<Life::OpenMPEngine>)->RangeMultiplier(4)->Range(1, maxFigureInRow)->Unit(benchmark::kMillisecond)->Name("OpenMp")->UseRealTime();
BENCHMARK(BM_LifeEngine<Life::ThreadEngine>)->RangeMultiplier(4)->Range(1, maxFigureInRow)->Unit(benchmark::kMillisecond)->Name("Thread")->UseRealTime();

