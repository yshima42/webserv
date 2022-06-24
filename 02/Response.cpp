#include "Response.hpp"

Response::Response() {}

Response::~Response() {}

Response::Response(Response const &other) { *this = other; }

Response &Response::operator=(Response const &other) {
  if (this != &other) {
  }
  return *this;
}
