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



class HTTPRequest
{
    public:
        HTTPRequest();
        virtual ~HTTPRequest();
        HTTPRequest(HTTPRequest const &other);
        HTTPRequest &operator=(HTTPRequest const &other);

    private:
		std::string _method;
		std::string _uri;
		std::string _protocol_version;
};

#endif
