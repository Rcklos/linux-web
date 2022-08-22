#include "kit/sock.h"
#include "log.h"
#include <string.h>
#include <netinet/in.h>
#include <assert.h>

int fish::create_socket_tcp_default(int port, socket_type_t type) {
  // 这里应该是client，暂不实现
  if(port ==  -1) port = 7000;
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  assert(sock >= 0);

  if(type == fish::SOCKET_TYPE_RECV) {
    LOGD("绑定端口: %d", port);
    int ret = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    assert(ret != -1);
  }
  return sock;
}
