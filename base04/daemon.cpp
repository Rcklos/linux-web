#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

bool daemonize() {
  pid_t pid = fork();       // 创建子进程
  if(pid < 0) return false;
  else if(pid > 0)  {
    std::cout << "正在退出父进程" << std::endl;
    sleep(10);
    exit(0); // 退出父进程
  }
  umask(0);
  pid_t sid = setsid();
  if(sid < 0) return false;
  if(chdir("/") < 0) return false;
  std::cout << "创建daemon进程成功" << std::endl;
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  return true;
}

int main() {
  daemonize();
  sleep(20);
  return 0;
}
