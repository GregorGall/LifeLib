#pragma once
#include <list>
#include <functional>

namespace Life {

  using cellGroup = std::list<std::pair<int, int>>;

  using makeFnc = std::function<cellGroup(int,int)>;

  cellGroup makeGlider(int row, int col);

  cellGroup makeStick(int row, int col);

  cellGroup makePond(int row, int col);

  cellGroup makeSquare(int row, int col);

  cellGroup makeToad(int row, int col);

  cellGroup makeBoat(int row, int col);

}
