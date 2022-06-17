#include "Server.hpp"

#include "HTTPRequest.hpp"

Server::Server(int accepted_fd) : fd_(accepted_fd) {}

Server::~Server() {}

int Server::run() {
  int request_size;

  HTTPRequest req(this);
  if ((request_size = req.recvRequestMessage()) <= 0) {
	  return -1;
  }

  //ここのエラー処理要検討
  if (req.parseRequestMessage() < 0) {
	  return -1;
  }
  //parseで入っているか確認
  /* printf("method: %s\n", method_); */
  /* printf("target: %s\n", target_); */

  //HTTPResponse res(req);
  

  return request_size;
}


int Server::get_fd_(){
	return fd_;
}

void Server::set_method_(char *method) {
	this->method_ = method;
}

void Server::set_target_(char *target) {
	this->target_ = target;
}

Server::Server(Server const &other) { *this = other; }

Server &Server::operator=(Server const &other) {
  if (this != &other) {
  }
  return *this;
}
