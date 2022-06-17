#include "HTTPResponse.hpp"

HTTPResponse::HTTPResponse() 
{

}

HTTPResponse::~HTTPResponse() {}

HTTPResponse::HTTPResponse(HTTPResponse const &other) { *this = other; }

HTTPResponse &HTTPResponse::operator=(HTTPResponse const &other) {
  if (this != &other) {
  }
  return *this;
}
