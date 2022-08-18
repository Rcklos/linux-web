#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>
#include <cstdlib>
#include <errno.h>
#include <string.h>
#include <iostream>

int main(int argc, char **argv){
  int port = 9000; // 默认端口号为9000
  if(argc == 2) port = atoi(argv[1]);
  std::cout << "即将监听: " << port << "端口" << std::endl;
  // 组合ip
  struct sockaddr_in addr;
  // 初始化
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;

  // 创建socket
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  assert(sock >= 0);
  int ret = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
  assert(ret != -1);
  ret = listen(sock, 5);
  assert(ret != -1);
  std::cout << "等待客户端连接中..." << std::endl;
  // 暂停20秒等待客户端连接
  sleep(20);
  struct sockaddr_in client;
  socklen_t client_addr_len = sizeof(client);
  // 获取客户端连接的描述符
  int connfd = accept(sock, (struct sockaddr*)&client, &client_addr_len);
  if(connfd < 0) std::cout << "errno: " << errno << std::endl;
  else {
    char remote[INET_ADDRSTRLEN];
    std::cout << "conn with ip: "
      << inet_ntop(AF_INET, &client.sin_addr, remote, INET_ADDRSTRLEN)
      << " port: "
      << ntohs(client.sin_port) << std::endl;
    close(connfd);
  }
  close(sock);
  return 0;
}
