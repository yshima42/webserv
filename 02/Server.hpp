#pragma once

#define MAX_CLIENTS 20
#include "Webserv.hpp"

class Server {
 public:
  Server(std::string port);
  virtual ~Server();
  Server(Server const &other);
  Server &operator=(Server const &other);

  int AcceptSelect();

  int shutdown();
  void close();

 private:
  int sock_;
  std::string address_;
  std::string port_;
  int clients_[MAX_CLIENTS];
  int clients_no_;
};
