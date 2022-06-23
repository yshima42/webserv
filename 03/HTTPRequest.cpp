#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest(int fd) : fd_(fd) { }

HTTPRequest::~HTTPRequest() {}

int HTTPRequest::recvRequestMessage() {

  if ((request_size_ =
           recv(fd_, &request_message_, sizeof(request_message_), 0)) == -1) {
    perror("recv");
    exit(1);
  } else if (request_size_ == 0) {
    return -1;
  }
  request_message_[request_size_] = '\0';
  fprintf(stderr, "request message: %s\n", request_message_);

  return request_size_;
}

int HTTPRequest::parseRequestMessage() {
  char *line;
  char *tmp_method;
  char *tmp_target;

  line = strtok(request_message_, "\n");

  tmp_method = strtok(line, " ");
  if (tmp_method == NULL) {
    printf("get method error\n");
    return -1;
  }
  method_ = tmp_method;

  tmp_target = strtok(NULL, " ");
  if (tmp_target == NULL) {
    printf("get target error\n");
    return -1;
  }
  target_ = tmp_target;

  return 0;
}

char * HTTPRequest::get_method_()
{
	return method_;
}

char * HTTPRequest::get_target_()
{
	return target_;
}

void HTTPRequest::set_target_(char *target)
{
	strcpy(target_, target);
}

HTTPRequest::HTTPRequest(HTTPRequest const &other) { *this = other; }

HTTPRequest &HTTPRequest::operator=(HTTPRequest const &other) {
  if (this != &other) {
  }
  return *this;
}
