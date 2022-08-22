#include "kit/sock.h"
#include "log.h"
#include <cstdlib>

#define BUFFER_SIZE 1024

using namespace fish;

int main(int argc, char **argv) {
  const char *ip = "127.0.0.1";
  int port = 9000;
  if(argc >=  2) port = atoi(argv[2]);
  if(argc >=  3) ip = argv[1];

  socket_t sockfd = fish::create_socket_tcp_default(SOCKET_TYPE_SEND);
  socket_addr_t *addr = fish::create_socket_addr(const_cast<char *>(ip), port);
  int ret = fish::connect(sockfd, addr);
  assert(ret != -1);

  char buffer[BUFFER_SIZE];
  // 还有buffer没写
}
