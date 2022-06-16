#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

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

#define SIZE 1024 * 5

class HTTPRequest
{
    public:
        HTTPRequest(int ws);
        virtual ~HTTPRequest();
        HTTPRequest(HTTPRequest const &other);
        HTTPRequest &operator=(HTTPRequest const &other);

		int recvRequestMessage();
		int perseRequestMessage();

		int get_ws();
		char *get_request_message();
		char *get_method();
		char *get_uri();
		char *get_protocol_version();

		void set_uri(char * new_uri);
		
		void show();

    private:
		int _ws;
		char _request_message[SIZE];
		int _request_size;
		char * _method;
		char * _uri;
		char * _protocol_version;
};

#endif
