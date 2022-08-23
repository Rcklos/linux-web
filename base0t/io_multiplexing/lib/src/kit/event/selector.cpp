#include "kit/event/selector.h"
#include "kit/sock.h"
#include "kit/thread_pool.h"
#include "log.h"
#include <sys/select.h>

using namespace fish;

void Selector::setup_() {

}

void Selector::run_() {
}

void Selector::loop_() {
  LOGD("test");
}

void single_select(socket_t sockfd, Task task) {
  fd_set sock_set;
  while(1) {

  }
}

void fish::select(socket_t sockfd, Task handle, bool enable_thread, int pool_size) {
  if(!enable_thread) {
    single_select(sockfd, handle);
    return;
  }
}
