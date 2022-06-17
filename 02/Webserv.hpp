#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <vector>
#include <sys/un.h>
#include <errno.h>
#include <map>

class Server;
// [socketの状態を監視してacceptできたものをHTTPRequestに送る]

#define MAX_CLIENTS 20

class Webserv
{
    public:
        Webserv(std::string port);
        virtual ~Webserv();
        Webserv(Webserv const &other);
        Webserv &operator=(Webserv const &other);

		void run();

    private:
		Server *server_;
		std::map<int, Server *> sockets_;
		int sock_; //readyできているsock -> 最終的にはここをvectorで持つ?
		fd_set fd_set_;
		unsigned int fd_size_;
		int max_fd_;

};

#endif
