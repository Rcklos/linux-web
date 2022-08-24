#ifndef __HTTP_HANDLE_H__
#define __HTTP_HANDLE_H__
#include "kit/sock.h"
#include "kit/thread_pool.h"
namespace fish {

class HttpHandle {
  private:
    ThreadPool *tpool_;
    void handle_(socket_t sockfd, char *buff_, int size);
  public:
    HttpHandle();
    ~HttpHandle();
    void handle(socket_t sockfd, char *buff_, int size);
};

}
#endif /* __HTTP_HANDLE_H__ */
