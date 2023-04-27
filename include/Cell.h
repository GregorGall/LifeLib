#pragma once
#include <atomic>

namespace Life {

  const int lifeThreshold = 3;
  const int minimumNeighboursToLive = 2;

  class Cell {

  public:

    void kill();

    void renew();

    bool toggle();

    void evolute();

    void increment();

    explicit operator bool() const;

  private:

    bool status{ false };

    std::atomic_int neighbours{ 0 };

  };

}
