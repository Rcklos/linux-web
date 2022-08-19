## 整理一下I/O的高级函数

### 1. pipe函数

```c++
#include <unistd.h>
int pipe(int fd[2]);

> 成功返回0, 失败返回-1并设置errno
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

### 2. dup和dup2

把标准输入重定向到文件或者把标准输出重定向到一个网络连接。

```c++
#include <unistd.h>

int dup(int file_descriptor);
int dup2(int file_descriptor_one, int file_descriptor_two);
```

dupp直接创建一个新文件描述符，指向file_descriptor同文件、管道或者网络连接。

dup2返回第一个不小于file_descriptor_two整数值。

### 3. readv和writev

将数据从文件描述符读到分散的内存块，即分散读。
将多块分散的内存数据一并写入文件描述符中，即集中写。

```c++
#include <sys/uio.h>

ssize_t readv(int fd, const struct iovec *vector, int count);
ssize_t writev(int fd, const struct iovec *vector, int count);
```

![集中写](http://cdn.lentme.cn/20220818151748.png)

### 4. sendfile函数

在两个文件描述符之间传递数据，实现零拷贝，避免了内核缓冲区和用户缓冲区之间的数据拷贝。

```c++
#include <sys/sendfile.h>

ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);
```

![零拷贝](http://cdn.lentme.cn/20220818184414.png)

### 5. mmap和munmap

mmap用于申请一段内存空间，作为进程共享内存，可以将文件直接映射其中。

munmap则释放这个共享内存

```c++
#include <sys/mman.h>

void *mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset);
int munmap(void *start, size_t length);
```

prot取值: 

- PROT_READ:  内存段可读
- PROT_WRITE: 内存段可写
- PROT_EXEC:  内存段可执行
- PROT_NONE:  内存段不能被访问

![flag](http://cdn.lentme.cn/20220818191019.png)

> mmap失败会设置errno并返回MAP_FAILED((void *)-1)
> munmap成功返回0,失败返回-1,并设置errno

### 6. splice函数

用于在两个文件描述符之间移动数据，也是零拷贝。

```c++
#include <fcntl.h>

ssize_t splice(int fd_in, loff_t *off_in, int fd_out, 
  loff_t *off_out, size_t len, unsigned int flags);
```

![splice的flag](http://cdn.lentme.cn/20220818191722.png)

> fd_in和fd_out至少要有一个是管道文件描述符。
> 成功则返回移动字节的数量，返回0则没有数据移动
> 失败返回-1和设置errno

搭建echo服务器：

![echo服务器](http://cdn.lentme.cn/20220818194101.png)

### 7. tee函数

在两个管道文件描述符之间复制数据，也是零拷贝，但是不消耗数据。

```c++
#include <fcntl.h>

ssize_t tee(int fd_in, int fd_out, size_t len, unsigned int flags);
```

> 参数接近splice，但要注意两个都是管道

利用tee和splice改进echo，实现同时回显和终端输出: 


