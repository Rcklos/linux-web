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
