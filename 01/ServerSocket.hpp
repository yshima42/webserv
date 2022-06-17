#ifndef SERVERSOCKET_HPP
# define SERVERSOCKET_HPP

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

#define MAX_CLIENTS 20

class ServerSocket
{
    public:
        ServerSocket(std::string port);
        virtual ~ServerSocket();
        ServerSocket(ServerSocket const &other);
        ServerSocket &operator=(ServerSocket const &other);

		int AcceptSelect();

		int shutdown();
		void close();

    private:
		int sock_;
		std::string address_;
		std::string port_;
		int clients_[MAX_CLIENTS];
		int clients_no_;
};

#endif
