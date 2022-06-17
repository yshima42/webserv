#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <vector>

#define SIZE 1024 * 5

class Server {
 public:
  Server(int accepted_fd);
  virtual ~Server();
  Server(Server const &other);
  Server &operator=(Server const &other);

  int run();

  int get_fd_();
  int get_status_();
  char *get_header_field_();
  int get_file_size_();
  char * get_body_();

  void set_method_(char *method);
  void set_target_(char *target);
  void set_status_(int status);
  void set_response_message_(char *message);
	
  int sendResponseMessage();

 private:
  int fd_;
  char *method_;
  char *target_;
  int status_;

  char body_[SIZE];
  char header_field_[SIZE];
  unsigned int file_size_;
  int response_size_;

  //とりあえずポインタにしているが微妙な気がする
  char *response_message_;

};

#endif
