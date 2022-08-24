#include "kit/event/base_server.h"
#include "kit/event/event_listener.h"
#include <functional>
#include "kit/http/http_handle.h"
#include "log.h"

using namespace fish;

class MyEventListener: public EventListener {
  private:
    HttpHandle http_handle;
  public:
    virtual void listen(event_t *event){ 
      LOGD("收到了event的消息: %s", event->buff);
      http_handle.handle(event->sockfd, event->buff, event->buff_size);
      if(event) delete event;
    }
};

int main() {
  BaseServer server;
  MyEventListener *listener = new MyEventListener();
  server.bind(9000)
    ->wait_for_accept(fish::SERVER_ACCEPT_SELECT, listener);
  delete listener;

  return 0;
}
