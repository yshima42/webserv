#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include "Server.hpp"

#define SIZE 1024 * 5

class HTTPRequest {
 public:
  HTTPRequest(Server *sv);
  virtual ~HTTPRequest();
  HTTPRequest(HTTPRequest const &other);
  HTTPRequest &operator=(HTTPRequest const &other);

  int recvRequestMessage();
  int parseRequestMessage();

 private:
  // int fd_;
  Server *sv_;
  char request_message_[SIZE];
  int request_size_;
};

#endif
