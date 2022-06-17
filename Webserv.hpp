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
		Server *_server;
		std::map<int, Server *> _sockets;
		int _sock; //readyできているsock -> 最終的にはここをvectorで持つ?
		fd_set _fd_set;
		unsigned int _fd_size;
		int _max_fd;

		std::string address;
		std::string port;
		int clients[MAX_CLIENTS];
		int clients_no;
};

#endif
