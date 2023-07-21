#pragma once
#include <deque>
#include <atomic>
#include <mutex>
#include <exception>
#include <vector>
#include <thread>
#include <future>
#include <functional>

namespace Life {

  class join_threads {

    std::vector<std::thread>& threads_;

  public:

    explicit join_threads(std::vector<std::thread>& threads): threads_(threads)
    {
    }

    ~join_threads(){
      for(unsigned long i=0; i < threads_.size(); ++i){
        if(threads_[i].joinable()){
          threads_[i].join();
        }
      }
    }

  };

  class ThreadPull {

  public:

    ThreadPull(): done(false), joiner(threads) {

      size_t threadCount = std::thread::hardware_concurrency();
      threadCount > 1 ? threadCount : threadCount = 1;

      try {
        for(size_t i = 0; i < threadCount; ++i){
          threads.push_back(std::thread(&ThreadPull::exec, this));
        }
      }
      catch(...){
        done = true;
        throw std::runtime_error("ThreadPull init failed");
      }

    }

    ~ThreadPull(){
      done = true;
    }

    size_t size(){
      return threads.size();
    }

    template<typename T>
    std::future<void> addTask(T f){

      std::packaged_task<task_t> pt(f);
      auto future = pt.get_future();

      std::lock_guard lk(taskMutex);
      taskQueue.push_back(std::move(pt));
      return future;
    }

  private:

    void exec() {

      while(!done){
        std::unique_lock lk(taskMutex);

        if(!taskQueue.empty()){
          auto task = std::move(taskQueue.front());
          taskQueue.pop_front();
          lk.unlock();

          task();
        }
        else {
          lk.unlock();
          std::this_thread::yield();
        }
      }

    }

  private:

    using task_t = void();

    std::mutex taskMutex;
    std::atomic_bool done;
    std::deque<std::packaged_task<task_t>> taskQueue;
    std::vector<std::thread> threads;
    join_threads joiner;

  };

}
