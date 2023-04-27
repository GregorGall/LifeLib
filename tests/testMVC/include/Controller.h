#pragma once
#include <thread>
#include <iostream>
#include <functional>
#include <unordered_map>

#include  "View.h"

class Controller {

public:

  Controller(Life::LifeModel& model, View& view);

  void launch();

  void createGlider(int row, int clmn);

private:

  void run();

  void stop();

  void boost();

  void slow();

  void toggle() { modelThread.joinable() ? stop() : run(); }

  void setEngine(Life::EngineType type, std::string name);

  void setCommon(){ setEngine(Life::EngineType::common, "Common"); }

  void setOpenMP(){ setEngine(Life::EngineType::openmp, "OpenMP"); }

  void setThread(){ setEngine(Life::EngineType::thread, "Thread"); }

private:

  using action = void(Controller::*)();

  View& view;
  Life::LifeModel& model;
  std::thread modelThread;
  std::chrono::milliseconds delay{ 200 };
  std::unordered_map<char, action> actionStore;

};
