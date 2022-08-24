#include "kit/event/event_listener.h"
#include <cstddef>
#include "log.h"
#include <functional>
#include <pthread.h>

using namespace fish;

EventListener::EventListener() {
  tpool = new ThreadPool(10);
}

EventListener::~EventListener() {
  if(tpool != NULL) delete tpool;
  tpool = NULL;
}

void EventListener::listen(event_t *event) {
  LOGD("default event listener");
}

void EventListener::emit(event_t *event) {
  tpool->addLast(std::bind(&EventListener::listen, this, event));
}
