#pragma once

namespace Life {

  class Cell {

  public:

    Cell(){};

    operator bool() const { return status; }

    void kill(){ status = false; };

    void renew(){ status = true; };

    void increment(){ ++neighbours; };

    void evolute()
    {
      if( neighbours == 3 ){ status = true; }
      if( neighbours > 3 ){ status = false; }
      if( neighbours < 2 ){ status = false; }
      neighbours = 0;
    };

  private:

    bool status{ false };

  public:
    int neighbours{ 0 };

  };

}
