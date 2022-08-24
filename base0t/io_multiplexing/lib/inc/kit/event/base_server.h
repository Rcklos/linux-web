#ifndef __BASE_SERVER_H__
#define __BASE_SERVER_H__

#include "kit/sock.h"

namespace fish {

typedef enum {
  SERVER_ACCEPT_SELECT,
  SERVER_ACCEPT_POLL,
  SERVER_ACCEPT_EPOLL,
} server_accept_t;

class BaseServer {
private:
    char *ip_;
    int port_;
    socket_t sockfd_;
    BaseServer *self_;
    bool enable_thread_pool_;

public:
  BaseServer();
  ~BaseServer();
  BaseServer *enbale_thread_pool();
  BaseServer *bind(char *ip, int port);
  BaseServer *bind(int port);
  void wait_for_accept(server_accept_t accept);
  socket_t sock();

private:
  // select服务器实现
  void select_accept();
};

}

#endif /** __BASE_SERVER_H__ **/
