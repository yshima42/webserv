#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include "HTTPServer.hpp"

#define SIZE 1024 * 5

class HTTPRequest {
 public:
  HTTPRequest(int fd);
  virtual ~HTTPRequest();
  HTTPRequest(HTTPRequest const &other);
  HTTPRequest &operator=(HTTPRequest const &other);

  int recvRequestMessage();
  int parseRequestMessage();

  char * get_method_();
  char * get_target_();

  void set_target_(char *target);

 private:
  int fd_;
  char *method_;
  char *target_;
  char request_message_[SIZE];
  int request_size_;
};

#endif
