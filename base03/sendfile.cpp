#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>
#include <cstdlib>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <iostream>

// sendfile
#include <sys/sendfile.h>

#define BUFFER_SIZE 1024

static const char *status_line[2] = {"200 OK", "500 Internal server error"};

int main(int argc, char **argv){
  int port = 9000; // 默认端口号为9000
  const char *file_name = "writev.txt";
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
    char header_buf[BUFFER_SIZE];
    memset(header_buf, '\0', BUFFER_SIZE);
    // 存放目标文件内容
    struct stat file_stat;
    bool valid = true;
    int len = 0;
    int filefd = -1;
    // 文件属性获取失败
    if(stat(file_name, &file_stat) < 0) valid = false;
    // 是否为一个目录
    else if(S_ISDIR(file_stat.st_mode)) valid = false;
    // 是否可读
    else if(file_stat.st_mode & S_IROTH) {
      filefd = open(file_name, O_RDONLY);
      assert(filefd > 0);
      std::cout << "文件检测合法可用" << std::endl;
    }
    else valid = false;
    if(!valid) {
      std::cout << "文件读取失败!!!" << std::endl;
      // 写入HTTP 500状态头
      ret = snprintf(header_buf, BUFFER_SIZE - 1, "%s %s\r\n", "HTTP/1.1", status_line[1]);
      len += ret;
      // header末尾分割符
      ret = snprintf(header_buf + len, BUFFER_SIZE - 1 - len, "%s", "\r\n");
      send(connfd, header_buf, strlen(header_buf), 0);
    } else {
      std::cout << "发送文件中..." << std::endl;
      // 写入HTTP 200状态头
      ret = snprintf(header_buf, BUFFER_SIZE - 1, "%s %s\r\n", "HTTP/1.1", status_line[0]);
      len += ret;
      // 写入数据长度header
      ret = snprintf(header_buf + len, BUFFER_SIZE - 1 - len, "Content-Length: %d\r\n",
          file_stat.st_size);
      len += ret;
      // header末尾分割符
      ret = snprintf(header_buf + len, BUFFER_SIZE - 1 - len, "%s", "\r\n");
      // 写header
      send(connfd, header_buf, strlen(header_buf), 0);
      // 零拷贝文件
      sendfile(connfd, filefd, NULL, file_stat.st_size);
      std::cout << "文件已发送" << std::endl;
    }
    close(connfd);
  }
  close(sock);
  return 0;
}
