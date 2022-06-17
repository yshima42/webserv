#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

#include "ServerSocket.hpp"

#define SIZE 1024 * 5

class HTTPRequest
{
    public:
        HTTPRequest(int ac_sock);
        virtual ~HTTPRequest();
        HTTPRequest(HTTPRequest const &other);
        HTTPRequest &operator=(HTTPRequest const &other);

		int recvRequestMessage();

    private:
		int ac_sock_;
		char request_message_[SIZE];
		int request_size_;
};

#endif
