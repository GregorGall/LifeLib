#pragma once
#include <atomic>

namespace Life {

  class Cell {

  public:

    Cell(){}

    operator bool() const { return status; }

    void kill(){ status = false; }

    void renew(){ status = true; }

    bool toggle(){ return status = !status; }

    void increment() { ++neighbours; }

    void evolute()
    {
      if( neighbours != 2) { status = (neighbours == 3); }
      neighbours = 0;
    }

  private:

    bool status{ false };

  public:

    std::atomic_int neighbours{ 0 };

  };

}
