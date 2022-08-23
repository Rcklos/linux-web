#include "base_server.h"
#include "kit/event/selector.h"
#include <unistd.h>
#include <assert.h>

using namespace fish;

BaseServer::BaseServer():
  ip_(nullptr),
  port_(-1),
  sockfd_(0),
  self_(this), 
  enable_thread_pool_(false) {}

BaseServer::~BaseServer() {
  close(sockfd_);
}

BaseServer* BaseServer::bind(char *ip, int port) {
  ip_ = ip;
  port_ = port;
  sockfd_ = create_socket_tcp_default(SOCKET_TYPE_RECV, port);
  assert(sockfd_ > 0);
  return self_;
}

BaseServer* BaseServer::bind(int port) {
  return self_->bind(NULL, port);
}

socket_t BaseServer::sock() { return sockfd_; }

void BaseServer::wait_for_accept(server_accept_t accept) {
  switch(accept) {
    case SERVER_ACCEPT_SELECT:
      self_->select_accept();
      break;
    case SERVER_ACCEPT_POLL:
    case SERVER_ACCEPT_EPOLL:
      break;
  }
}

void BaseServer::select_accept() {
  // fish::select(this->fd);
}