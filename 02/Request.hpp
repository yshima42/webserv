#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include "Webserv.hpp"

#define SIZE 1024 * 5

class Request {
 public:
  Request(int ac_sock);
  virtual ~Request();
  Request(Request const &other);
  Request &operator=(Request const &other);

  int recvRequestMessage();

 private:
  int ac_sock_;
  char request_message_[SIZE];
  int request_size_;
};

#endif
