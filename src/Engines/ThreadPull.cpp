#include "ThreadEngine/ThreadPull.h"

/*!
 * \details
 * Инициализируем вектор потоков
 */
Life::ThreadPull::ThreadPull(): done(false), joiner(threads) {

  // Метод может вернуть 0, поэтому  нужна проверка
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

/*!
 * \details
 */
Life::ThreadPull::~ThreadPull(){
  done = true;
}

/*!
 * \details
 */
size_t Life::ThreadPull::size(){
  return threads.size();
}

/*!
 * \details
 * В методе реализуется цикл по ожиданию появления задач в очереди и
 * запуску из исполнения.
 */
void Life::ThreadPull::exec() {

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
