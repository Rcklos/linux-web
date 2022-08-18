#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>
#include <cstdlib>
#include <errno.h>
#include <string.h>
#include <iostream>

int main(int argc, char **argv) {
  int port = 9000; // 默认端口号为9000
  if(argc == 2) port = atoi(argv[1]);
  std::cout << "即将连接: " << port << "端口" << std::endl;
  // 组合ip
  struct sockaddr_in server_addr;
  // 初始化
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // 创建socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  assert(sockfd >= 0);
  // 连接服务器
  if(connect(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
    std::cout << "connection failed!" << std::endl;
    return 0;
  }
  const char *oob_data = "abc";
  const char *normal_data = "123";
  send(sockfd, normal_data, strlen(normal_data), 0);
  send(sockfd, oob_data, strlen(oob_data), MSG_OOB);
  send(sockfd, normal_data, strlen(normal_data), 0);
  close(sockfd);
  return 0;
}
