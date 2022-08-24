#include "kit/event/base_server.h"

using namespace fish;
int main() {
  BaseServer server;
  server.bind(9000)
    ->wait_for_accept(fish::SERVER_ACCEPT_SELECT);
  return 0;
}
