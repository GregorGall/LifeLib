#include "Controller.h"

Controller::Controller(Life::LifeModel &model, View &view): model{ model }, view{ view }
{
 actionStore['w'] = &Controller::boost;
 actionStore['s'] = &Controller::slow;
 actionStore[' '] = &Controller::toggle;
 actionStore['1'] = &Controller::setCommon;
 actionStore['2'] = &Controller::setOpenMP;
 actionStore['3'] = &Controller::setThread;
}

void Controller::launch()
{
  system("stty raw; stty -echo; stty opost");
  model.setDelay(delay);

  char cmd = ' ';
  while(cmd != 'q') {
      if(actionStore.contains(cmd)){ std::invoke(actionStore[cmd], *this); }
      cmd = getc(stdin);
  }

  if(modelThread.joinable()){ stop(); }
  system("stty sane");
}

void Controller::testLaunch(int generationNum)
{
  auto counter = [&](){
    static int generation = 0;
    if(++generation >= generationNum){
      model.stop();
    }

    view.show();
  };

  modelThread = std::thread(&Life::LifeModel::run, std::ref(model), counter);
  modelThread.join();
}

void Controller::run()
{
    view.toggleLife();
    modelThread = std::thread(&Life::LifeModel::run, std::ref(model), [&](){ view.show(); });
}

void Controller::stop()
{
    model.stop();
    view.toggleLife();
    modelThread.join();
}

void Controller::boost()
{
    model.setDelay(delay -= std::chrono::milliseconds(50));
    view.redraw();
}

void Controller::slow()
{
    model.setDelay(delay += std::chrono::milliseconds(50));
    view.redraw();
}

void Controller::setEngine(Life::EngineType type, std::string name)
{
    model.setEngine(type);
    view.setEngine(name);
    view.redraw();
}


void Controller::createGlider(int row, int col)
{
    using cellGroup = std::list<std::pair<int, int>>;
    cellGroup glider{ {row, col},
                      {row + 1, col + 1},
                      {row + 1, col + 2},
                      {row + 2, col    },
                      {row + 2, col + 1} };

    model.toggleGroup(glider);
    view.redraw();
}
