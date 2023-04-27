#pragma once
#include "View.h"
#include "Controller.h"

class App {

public:

  App(): model(20, 26), view(model), ctrl(model, view)
  {
  }

  int exec();

private:

  void createSwarm(int rowNum, int colNum);

private:

    View view;
    Controller ctrl;
    Life::LifeModel model;

};
