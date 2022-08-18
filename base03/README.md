## 整理一下I/O的高级函数

### pipe函数

```c++
#include <unistd.h>
int pipe(int fd[2]);
```

创建双向管道: 

```c++
#include <sys/types.h>
#include <sys/socket.h>

/**
 * domain: AF_UNIX only,
 * 前三个和socket一样，最后一个参数和pipe一样
 */
int socketpair(int domain, int type, int protocol, int fd[2]);
```

### dup和dup2

把标准输入重定向到文件或者把标准输出重定向到一个网络连接。

```c++
#include <unistd.h>

int dup(int file_descriptor);
int dup2(int file_descriptor_one, int file_descriptor_two);
```

dupp直接创建一个新文件描述符，指向file_descriptor同文件、管道或者网络连接。

dup2返回第一个不小于file_descriptor_two整数值。

### readv和writev

将数据从文件描述符读到分散的内存块，即分散读。
将多块分散的内存数据一并写入文件描述符中，即集中写。

```c++
#include <sys/uio.h>

ssize_t readv(int fd, const struct iovec *vector, int count);
ssize_t writev(int fd, const struct iovec *vector, int count);
```

![集中写](http://cdn.lentme.cn/20220818151748.png)

### sendfile函数

在两个文件描述符之间传递数据，实现零拷贝，避免了内核缓冲区和用户缓冲区之间的数据拷贝。

```c++
#include <sys/sendfile.h>

ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);
```


