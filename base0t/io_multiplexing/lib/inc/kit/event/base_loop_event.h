#ifndef __BASE_LOOP_EVENT_H__
#define __BASE_LOOP_EVENT_H__

#include "kit/thread_pool.h"
#include "kit/sock.h"
namespace fish {

class BaseLoopEventGroup {
protected:
  socket_t sockfd_;
  int pool_size_;
  bool running_;

  virtual void setup_();
  virtual void loop_();

public:
  BaseLoopEventGroup(int pool_size = 0);
  ~BaseLoopEventGroup();
  void terminal();
  void loop(const Task &thread);

private:
  ThreadPool *thread_pool_;
};

}
#endif /* __BASE_LOOP_EVENT_H__ */
