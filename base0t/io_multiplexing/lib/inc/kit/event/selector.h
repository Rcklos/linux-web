#ifndef __SELECTOR_H__
#define __SELECTOR_H__
#include "kit/event/base_loop_event.h"
#include "kit/thread_pool.h"
#include "kit/sock.h"
namespace fish{

class Selector: public BaseLoopEventGroup {
private:
  void setup_();
  void run_();
  void loop_();
};

void select(socket_t sockfd, Task handle, bool enable_thread = false, int pool_size = 5);

}
#endif /** __SELECTOR_H__ **/
