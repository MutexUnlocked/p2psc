#pragma once

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <p2psc/socket/socket_address.h>
#include <p2psc/socket/socket_exception.h>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>

namespace p2psc {

class Socket {
public:
  Socket(const socket::SocketAddress &socket_address);
  ~Socket();

  void send(const std::string &);
  std::string receive();

private:
  void _connect();
  void _check_is_open();

  int _sock_fd;
  bool _is_open;
  struct sockaddr_in _address;
};
}