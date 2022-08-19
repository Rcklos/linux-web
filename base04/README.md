# Linux服务器编程规范

- linux服务器程序一般以守护进程形式运行。
- linux服务器程序通常拥有一套日志系统。
- linux服务器程序一般以非root身份运行。
- linux服务器程序通常是可配置的，当需要许多命令行选项时，采用配置文件，并存放在/etc目录下。
- linux服务器程序通常会在启动时生成pid文件存放于/var/run目录下。
- linux服务器程序通常需要考虑系统资源和限制。

## 1. 日志

### 1.1 Linux系统日志

![linux系统日志](http://cdn.lentme.cn/20220819143329.png)

### 1.2 syslog函数

```c++
#include <syslog.h>

void syslog(int priority, const char *messgae, ...);
```

![priority](http://cdn.lentme.cn/20220819160841.png)

#### 修改syslog默认输出方式:

```c++
#include <syslog.h>

void openlog(const char *ident, int logopt, int facility);
```

ident参数指定字符串将被添加到日志消息的日期和时间之后，通常为程序的名字。

logopt: 按位取值

![logopt](http://cdn.lentme.cn/20220819161225.png)

facility: 指定syslog默认设施值

#### 日志过滤

开关调试信息使用日志掩码。

```c++
#include <syslog.h>

int setlogmask(int maskpri);
```

#### 关闭日志功能

```c++
#include <syslog.h>

void closelog();
```

## 2. 用户信息

### 2.1 UID、EUID、GID和EGID

- UID: 当前进程的真实用户ID
- EUID: 有效用户ID
- GID: 真实组ID
- EGID: 有效组ID

```c++
#include <sys/types.h>
#include <unistd.h>

uid_t getuid();
uid_t geteuid();

gid_t getgid();
gid_t getegid();

// set省略
```

查看当前进程用户ID及组ID: (uid.cpp)

![查看用户及用户组ID](http://cdn.lentme.cn/20220819165709.png)

切换用户栗子(switch_user.cpp)
![切换用户](http://cdn.lentme.cn/20220819165625.png)

## 3. 进程间关系

### 3.1 进程组

```c++
#include <unistd.h>

pid_t getpgid(pid_t pid);
```

> 查看进程组，返回进程组PGID，失败返回-1并设置errno

设置PGID: 

```c++
#include <unistd.h>

int setpgid(pid_t pid, pid_t pgid);
```

> 成功返回0，失败返回-1并设置errno

### 3.2 会话

会话(session)由一些相关联的进程组形成。

创建会话: 

```c++
#include <unistd.h>

pid_t setsid(void);
```

- 调用进程是会话的首领，此时会话刚创建。
- 新建一个进程组，PGID就是调用进程的PID，调用进程成为该首领。
- 调用进程将甩开终端。

### 3.3 ps命令查看进程关系

![ps命令和bat命令](http://cdn.lentme.cn/20220819170643.png)

图示(需要把less改成bat)：

![进程关系图示](http://cdn.lentme.cn/20220819171003.png)

## 4. 系统资源限制

资源限制读取

```c++
#include <sys/resource.h>

int getrlimit(int resource, struct rlimit *rlim);
int setrlimit(int resource, const struct rlimit *rlim);
```

rlim: 

```c++
struct rlimit {
  // rlim_t 是整数类型
  rlim_t rlim_cur; // 资源软限制
  rlim_t rlim_max; // 资源硬限制
}
```

![资源类型](http://cdn.lentme.cn/20220819171505.png)

## 5. 改变工作目录和根目录

```c++
#include <unistd.h>

char *getcwd(char *buf, size_t size);
char chdir(const char *path);
int chroot(const char *path);
```

> 只有特权进程才能修改根目录

## 6. 服务器程序后台化

linux提供: 

```c++
#include <unistd.h>

int daemon(int nochdir, int noclose);
```

自己实现(daemon.cpp):

```c++
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
```
