#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>

// pipe
#include <unistd.h>
// splice, tee
#include <fcntl.h>

#define BUFFER_SIZE 1024

static const char *status_line[2] = {"200 OK", "500 Internal server error"};


void tee_handle(int connfd) {
  int pipefd[2], pipe_stdout[2], ret = -1;
  ret = pipe(pipefd);
  ret = pipe(pipe_stdout);
  // 接受来自connfd的数据
  ret = splice(connfd, NULL, pipefd[1], NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
  assert(ret != -1);
  // 复制管道
  ret = tee(pipefd[0], pipe_stdout[1], 32768, SPLICE_F_NONBLOCK);
  assert(ret != -1);
  // 回显
  ret = splice(pipe_stdout[0], NULL, connfd, NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
  assert(ret != -1);
  // 终端输出(STDOUT_FILENO invalid argument wsl(2)都是有问题的)
  ret = splice(pipefd[0], NULL, STDOUT_FILENO, NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
  std::cout << "errno: " << std::strerror(errno) << std::endl;
  assert(ret != -1);
  for(int i = 0; i < 2; i++) {
    close(pipefd[i]);
    close(pipe_stdout[i]);
  }
}

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
  // 复用TIME_WAIT，调试用
  int reuse = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
  int ret = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
  assert(ret != -1);
  ret = listen(sock, 5);
  assert(ret != -1);
  std::cout << "等待客户端连接中..." << std::endl;
  struct sockaddr_in client;
  socklen_t client_addr_len = sizeof(client);
  // 获取客户端连接的描述符
  int connfd = accept(sock, (struct sockaddr*)&client, &client_addr_len);
  if(connfd < 0) std::cout << "errno: " << errno << std::endl;
  else {
    // 输出连接
    char remote[INET_ADDRSTRLEN];
    std::cout << "连接到ip: "
      << inet_ntop(AF_INET, &client.sin_addr, remote, INET_ADDRSTRLEN)
      << " port: "
      << ntohs(client.sin_port) << std::endl;

    // tee
    tee_handle(connfd);

    close(connfd);
  }
  close(sock);
  return 0;
}
