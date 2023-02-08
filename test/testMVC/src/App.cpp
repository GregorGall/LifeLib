#include "App.h"

void App::createSwarm(int rowNum, int colNum)
{
  int figureStep = 5;
  for(int i = 0; i < rowNum; ++i) {
    for(int j = 0; j < colNum; ++j) {
      ctrl.createGlider(i * figureStep, j * figureStep);
    }
  }
}


int App::exec()
{
    createSwarm(2,3);
    ctrl.launch();
    return 0;
}
