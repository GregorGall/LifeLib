#pragma once
#include <thread>

namespace Life {

  class jthread {

  public:

      jthread(){}

      template<typename ...args>
      jthread(args... fargs)
      {
        someThread = std::thread(fargs...);
      }

      ~jthread()
      {
        if(someThread.joinable()){ someThread.join(); }
      }

      jthread(jthread&& other)
      {
        someThread = std::move(other.someThread);
      }

      jthread& operator=(jthread&& other)
      {
        if ( someThread.joinable() ) { someThread.join(); }
        someThread = std::move(other.someThread);
        return *this;
      }

  private:

      std::thread someThread;

  };

}
