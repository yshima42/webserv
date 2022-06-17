#include "Server.hpp"

#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"

Server::Server(int accepted_fd) : fd_(accepted_fd) {}

Server::~Server() {}

unsigned int getFileSize(const char *path) {
    int size, read_size;
    char read_buf[SIZE];
    FILE *f;

    f = fopen(path, "rb");
    if (f == NULL) {
        return 0;
    }

    size = 0;
    do {
        read_size = fread(read_buf, 1, SIZE, f);
        size += read_size;
    } while(read_size != 0);

    fclose(f);

    return size;
}

int getProccessing(char *body, char *file_path) {
	FILE *f;
	int file_size;

	file_size = getFileSize(file_path);
	if (file_size == 0) {
		printf("getFileSize error\n");
		return 404;
	}
	f = fopen(file_path, "r");
	fread(body, 1, file_size, f);
	fclose(f);

	return 200;
}

int Server::sendResponseMessage() {
	int send_size;

	send_size = send(fd_, response_message_, response_size_, 0);

	return send_size;
}

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

  //この部分をどこでやるか要検討
  if (strcmp(method_, "GET") == 0) {
	  if (strcmp(target_, "/") == 0) {
		  strcpy(target_, "/index.html");
	  }
	  status_ = getProccessing(body_, &target_[1]);
  } else {
	  status_ = 404;
  }

  //確認用
  /* printf("status: %d\n", status_); */
  /* printf("body: %s\n", body); */

  //ヘッダーフィールド作成
  file_size_ = getFileSize(&target_[1]);
  sprintf(header_field_, "Content-Length: %u\r\n", file_size_);
  printf("header_field: %s\n", header_field_);

  HTTPResponse res(this);
  response_size_ = res.createResponseMessage();

  //確認用
  //printf("response_message_: %s\n", response_message_);
  
  this->sendResponseMessage();

  return request_size;
}


int Server::get_fd_(){
	return fd_;
}

int Server::get_status_() {
	return status_;
}

char * Server::get_header_field_() {
	return header_field_;
}

int Server::get_file_size_() {
	return file_size_;
}

char * Server::get_body_() {
	return body_;
}

void Server::set_method_(char *method) {
	this->method_ = method;
}

void Server::set_target_(char *target) {
	this->target_ = target;
}

void Server::set_status_(int status) {
	this->status_ = status;
}

void Server::set_response_message_(char *message) {
	this->response_message_ = message;
}

Server::Server(Server const &other) { *this = other; }

Server &Server::operator=(Server const &other) {
  if (this != &other) {
  }
  return *this;
}
