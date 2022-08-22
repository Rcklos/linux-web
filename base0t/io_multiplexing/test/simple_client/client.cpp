#include "kit/sock.h"
#include "log.h"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>

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

  std::string str;
  // char buffer[BUFFER_SIZE];
  // bzero(buffer, BUFFER_SIZE);
  // 后面还没写
  while(1) {
    std::cin >> str;
    LOGD("发送消息: %s", str.c_str());
    send(sockfd, str.c_str(), str.length(), 0);

    if(std::strstr(str.c_str(), "stop__")) break;
  }
  LOGD("bye");
}
