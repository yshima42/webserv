#include "HTTPServer.hpp"

#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"

HTTPServer::HTTPServer(int accepted_fd) : fd_(accepted_fd) {}

HTTPServer::~HTTPServer() {}

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
  } while (read_size != 0);

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

int HTTPServer::sendResponseMessage() {
  int send_size;

  printf("fd: %d\n", fd_);
  send_size = send(fd_, response_message_, response_size_, 0);

  return send_size;
}

// めちゃめちゃでかいリクエストが来た時 中途半端にメッセージ作って送っちゃう
// ものすごいでかいボディができた時
// => recvとsendの処理をわける
int HTTPServer::run() {
  int request_size;

  HTTPRequest req(fd_);
  if ((request_size = req.recvRequestMessage()) <= 0) {
    return -1;
  }

  //ここのエラー処理要検討
  if (req.parseRequestMessage() < 0) {
    return -1;
  }

  // parseで入っているか確認
  printf("method: %s\n", req.get_method_());
  printf("target: %s\n", req.get_target_());

  //この部分をどこでやるか要検討
  if (strcmp(req.get_method_(), "GET") == 0) {
    if (strcmp(req.get_target_(), "/") == 0) {
		req.set_target_(strdup("/index.html"));
    }
    status_ = getProccessing(body_, &req.get_target_()[1]);
  } else {
    status_ = 404;
  }

  //確認用
  /* printf("status: %d\n", status_); */
  /* printf("body: %s\n", body); */

  //ヘッダーフィールド作成
  file_size_ = getFileSize(&req.get_target_()[1]);
  sprintf(header_field_, "Content-Length: %u\r\n", file_size_);
  // printf("header_field: %s\n", header_field_);

  HTTPResponse res(this);
  response_size_ = res.createResponseMessage();

  //確認用
  printf("response_message_: %s\n", response_message_);

  this->sendResponseMessage();

  return request_size;
}

int HTTPServer::get_fd_() { return fd_; }

int HTTPServer::get_status_() { return status_; }

char *HTTPServer::get_header_field_() { return header_field_; }

int HTTPServer::get_file_size_() { return file_size_; }

char *HTTPServer::get_body_() { return body_; }

void HTTPServer::set_status_(int status) { this->status_ = status; }

void HTTPServer::set_response_message_(char *message) {
  this->response_message_ = message;
}

HTTPServer::HTTPServer(HTTPServer const &other) { *this = other; }

HTTPServer &HTTPServer::operator=(HTTPServer const &other) {
  if (this != &other) {
  }
  return *this;
}
