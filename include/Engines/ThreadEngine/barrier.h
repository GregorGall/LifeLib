#pragma once
#include <mutex>
#include <condition_variable>

namespace Life {

  class barrier {

  public:

      barrier(){}

      void wait()
      {
          std::unique_lock lk(syncMutex);

          ++syncThread;
          threadNum == syncThread ? wakeUp() : syncVar.wait(lk);

          lk.unlock();
      }

      void reset(int threadToSync) { threadNum = threadToSync; }

  private:

      void wakeUp()
      {
          syncVar.notify_all();
          syncThread = 0;
      }

  private:

      int threadNum{ 1 };
      int syncThread{ 0 };
      std::mutex syncMutex;
      std::condition_variable syncVar;

  };

}
