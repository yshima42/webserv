#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP

#include "HTTPRequest.hpp"

class HTTPResponse
{
    public:
        HTTPResponse(HTTPRequest *req);
        virtual ~HTTPResponse();
        HTTPResponse(HTTPResponse const &other);
        HTTPResponse &operator=(HTTPResponse const &other);

    private:
		int _ws;
		char * _method;
		char * _uri;
		char * _protocol_version;

		int status;
		char body[SIZE];
		unsigned int file_size;
		char header_field[SIZE];

};

#endif
