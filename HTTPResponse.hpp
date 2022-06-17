#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include "HTTPRequest.hpp"
#include "Server.hpp"

class HTTPResponse {
 public:
  HTTPResponse(Server *sv);
  virtual ~HTTPResponse();
  HTTPResponse(HTTPResponse const &other);
  HTTPResponse &operator=(HTTPResponse const &other);

  int createResponseMessage();

 private:
  Server *sv_;
  char response_message_[SIZE];
};

#endif
