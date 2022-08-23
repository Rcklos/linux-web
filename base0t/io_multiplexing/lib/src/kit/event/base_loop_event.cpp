#include "kit/event/base_loop_event.h"
#include "kit/thread_pool.h"
#include "log.h"
#include <functional>

using namespace fish;

void BaseLoopEventGroup::setup_() {}
void BaseLoopEventGroup::loop_() {}

BaseLoopEventGroup::BaseLoopEventGroup(int pool_size):
  sockfd_(0),
  pool_size_(pool_size),
  running_(true),
  thread_pool_(nullptr){}

BaseLoopEventGroup::~BaseLoopEventGroup() {
  this->terminal();
}

void BaseLoopEventGroup::terminal() {
  if(!running_) return;
  LOGD("BaseLoopEventGroup: terminal");
  running_ = false;
  if(thread_pool_ != NULL) delete thread_pool_;
}


void BaseLoopEventGroup::loop(const Task &thread) {
  setup_();
  if(thread && pool_size_ > 0) {
    thread_pool_ = new ThreadPool(pool_size_);
    LOGD("pool size: %d", pool_size_);
    for(int i = 0; i < pool_size_; i++) 
      thread_pool_->addLast(thread);
  }
  LOGD("BaseLoopEventGroup: running_ = %d", running_);
  while(running_)
    loop_();
  LOGD("BaseLoopEventGroup: bye");
}
