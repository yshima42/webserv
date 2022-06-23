#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <vector>

#include "HTTPServer.hpp"

#define MAX_CLIENTS 20

// socketやacceptを行い、HTTPServerにつなげる
class Webserv {
 public:
  Webserv(std::string port);
  virtual ~Webserv();
  Webserv(Webserv const &other);
  Webserv &operator=(Webserv const &other);

  void loop();
  int shutdown();
  void close();

 private:
  int sock_;
  std::string address_;
  std::string port_;
  int clients_[MAX_CLIENTS];
  int clients_no_;
};

#endif
