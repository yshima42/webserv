#ifndef SOCKET_HPP
# define SOCKET_HPP

#include <iostream>
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

class ServerSocket
{
    public:
		//ServerSocket(int domain, int type, int protocol);
		ServerSocket(std::string portnm);
		//int bind(std::string ip, std::string port);
		//int listen(int max_queue);
		//int accept();
		int shutdown();
		void close();

		int getSock();
		//int connect(std::string ip, std::string port);
		int AcceptLoopSelect();

        ~ServerSocket();
        ServerSocket(ServerSocket const &other);
        ServerSocket &operator=(ServerSocket const &other);

    private:
		int sock;
		std::string address;
		std::string port;
		//struct sockaddr_in sa;
};

		
#endif
