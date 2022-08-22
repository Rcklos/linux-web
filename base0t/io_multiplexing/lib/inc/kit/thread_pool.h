#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <pthread.h>
#include <queue>
#include <functional>

namespace G {


class ThreadPool {
  typedef int th_size_t;
  // typedef void* (*th_func_t)(void);
  // 需要引入： #include <functional>
  typedef std::function<void()> th_func_t;
private:
  ThreadPool*self;
  th_size_t max_size_;
  pthread_t *threads_;

public:
  ThreadPool();
  explicit ThreadPool(th_size_t max_size = 0);
  ~ThreadPool();
  void addLast(const th_func_t& func);
  th_size_t size();
  void terminal();

private:
  bool stop_;
  pthread_mutex_t mutex_;
  pthread_cond_t cond_;
  std::queue<th_func_t> mq;
  static void* th_create(void *args);

  th_func_t recv_task();
};
}

#endif /** __THREAD_POOL_H__ **/
