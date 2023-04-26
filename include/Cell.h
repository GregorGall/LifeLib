#pragma once
#include <atomic>

namespace Life {

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

  public:

    std::atomic_int neighbours{ 0 };

  };

}
