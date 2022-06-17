#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest(int ac_sock)
	:ac_sock_(ac_sock)
{
	
}

HTTPRequest::~HTTPRequest()
{
}

int HTTPRequest::recvRequestMessage()
{
	if ((request_size_ = recv(ac_sock_, &request_message_, sizeof(request_message_), 0)) == -1) {
		perror("recv");
		exit(1);
	} else if (request_size_ == 0) {
		return -1;
	}
	request_message_[request_size_] = '\0';
	fprintf(stderr, "request message: %s\n", request_message_);

	return 0;
}

HTTPRequest::HTTPRequest(HTTPRequest const &other)
{
    *this = other;
}

HTTPRequest &HTTPRequest::operator=(HTTPRequest const &other)
{
    if (this != &other)
    {
    }
    return *this;
}
