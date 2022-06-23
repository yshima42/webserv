#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include "HTTPRequest.hpp"
#include "HTTPServer.hpp"

class HTTPResponse {
 public:
  HTTPResponse(HTTPServer *sv);
  virtual ~HTTPResponse();
  HTTPResponse(HTTPResponse const &other);
  HTTPResponse &operator=(HTTPResponse const &other);

  int createResponseMessage();

 private:
  HTTPServer *sv_;
  char response_message_[SIZE];
};

#endif
