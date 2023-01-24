#pragma once

namespace Life {

  class Cell {

  public:

    Cell(){};

    operator bool() const { return status; }

    void kill(){ status = false; };

    void renew(){ status = true; };

    void increment(){ ++neighbours; };

    void evolute() { neighbours == 3 || neighbours == 2 ? status = true : status = false; };

  private:

    bool status{ false };
    int neighbours{ 0 };

  };

}
