#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <deque>

#include "LifeModel.h"

class View{

public:

  View(Life::LifeModel& model): model{ model }
  {
  }

  void setEngine(std::string type){ engineType = type; }

  void toggleLife();

  void redraw();

  void show();

private:

  void printCols();

  void drawHeader();

  void drawDesk();

  void drawControl();

  void clear() { system("clear"); }

  template<typename T>
  void printSym(T sym, int width = 2) { std::cout << std::setw(width) << sym;  }

private:

  int generation{ 0 };
  std::string loaderState[3]{"\\", "/", "_"};
  std::string lifeState[2]{"stopped", "executes"};
  std::string engineType{"Common"};
  Life::LifeModel& model;

};
