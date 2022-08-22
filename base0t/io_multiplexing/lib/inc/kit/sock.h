#ifndef __UTIL_SOCK_H__
#define __UTIL_SOCK_H__

#define DEFAULT_SOCK_PORT 9000

namespace fish{

typedef int socket_t;

/**
 * @addr 目前是sockaddr_in
 */
typedef struct {
  const char *ip;
  int port;
  void *sockaddr;
} socket_addr_t;

typedef enum {
  SOCKET_TYPE_RECV,
  SOCKET_TYPE_SEND
} socket_type_t;

/**
 * @deprecated
 * @brief 默认值初始化socket
 * @param port 端口
 * @param type 类型
 * @return 成功返回sockfd, 失败返回-1
 */
int create_socket_tcp_default(int port, socket_type_t type);

/**
 * @brief 默认值初始化socket
 * @param type 类型
 * @param port 端口
 * @return 成功返回sockfd, 失败返回-1
 */
socket_t create_socket_tcp_default(socket_type_t type, int port = -1);

socket_addr_t* create_socket_addr(char *ip, int port);
void free_socket_addr(socket_addr_t *addr);

int connect(socket_t socket, socket_addr_t* addr);
}
#endif /** __UTIL_SOCK_H__ **/
