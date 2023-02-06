#include "View.h"

void View::show()
{
    ++generation;
    redraw();
}

void View::redraw()
{
    clear();
    drawHeader();
    drawDesk();
    drawControl();
}

void View::toggleLife()
{
    std::swap(lifeState[0], lifeState[1]); redraw();
}

void View::printCols()
{
    printSym('a', 4);
    for(int i = 1; i < model.readData().cols(); ++i) {
      printSym(char('a' + i));
    }
    std::cout << std::endl;
}

void View::drawHeader()
{
    std::cout << "Engine: "<< engineType << ", ";
    std::cout << "Delay: " << model.readDelay().count() << "ms" << ", ";
    std::cout << "Generation: " << generation << " ";
    std::cout << lifeState[0] << " " << loaderState[generation % 3] << std::endl;
}

void View::drawDesk()
{
    auto& data = model.readData();

    printCols();
    for(int i = 0; i < data.rows(); ++i) {
      printSym(i);
      for(int j = 0; j < data.cols(); ++j) {
        data(i, j) ? printSym('*') : printSym(' ');
      }

      std::cout << std::endl;
    }
}

void View::drawControl()
{
    std::cout << "Control: run/pause(space), boost(w), slow(s), engine(1/2/3), quit(q)" << std::endl;
}
