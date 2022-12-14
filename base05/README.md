## 高性能服务框架程序

服务器解构为以下三个主要模块: 

- IO处理单元
- 逻辑单元
- 存储单元

### 1. 服务器模型

#### 1.1 C/S模型

![C/S模型](http://cdn.lentme.cn/20220820195247.png)

#### 1.2 P2P模型

放弃以服务器为中心的格局，让所有主机都回归对等地位。

缺点是主机之间难以被发现，用户之间传输请求过多时网络负载加重。

![两种P2P模型](http://cdn.lentme.cn/20220820195451.png)

### 2. 服务器编程框架

![服务器基本框架](http://cdn.lentme.cn/20220820195531.png)

### 3. IO模型

![IO模型](http://cdn.lentme.cn/20220820195651.png)

> 几种IO模型刚好都对应着: 同步、select、poll、epoll

### 4. 两种事件处理模式

两种模式： `Reactor`和`Proactor`模式。

#### Reactor模式

要求主线程监听文件描述符是否有事件发生，若有则立即通知工作线程。

![Reactor](http://cdn.lentme.cn/20220820195935.png)

#### Proactor模式

IO操作都交给主线程和内核处理，工作线程仅负责业务逻辑。

![Proactor](http://cdn.lentme.cn/20220820200215.png)

### 5. 两种高效的并发模式


