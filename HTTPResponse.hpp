#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include "HTTPRequest.hpp"

class HTTPResponse {
 public:
  HTTPResponse();
  virtual ~HTTPResponse();
  HTTPResponse(HTTPResponse const &other);
  HTTPResponse &operator=(HTTPResponse const &other);

 private:
  //int status_;

};

#endif
