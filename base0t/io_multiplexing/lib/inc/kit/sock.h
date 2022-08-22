#ifndef __UTIL_SOCK_H__
#define __UTIL_SOCK_H__


namespace fish{

typedef enum {
  SOCKET_TYPE_RECV,
  SOCKET_TYPE_SEND
} socket_type_t;

/**
 * @brief 默认值初始化socket
 * @param port 端口
 * @return 成功返回sockfd, 失败返回-1
 */
int create_socket_tcp_default(int port, socket_type_t type);
}
#endif /** __UTIL_SOCK_H__ **/
