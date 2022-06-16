#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest(int ws)
	:_ws(ws)
{

}

HTTPRequest::~HTTPRequest()
{
}

int HTTPRequest::recvRequestMessage()
{
	if ((_request_size = recv(_ws, &_request_message, sizeof(_request_message), 0)) == -1) {
		perror("read");
		exit(1);
	} else if (_request_size == 0) {
		return -1;
	}
	_request_message[_request_size] = '\0';

	printf("%s", _request_message);

	return 0;
}

int HTTPRequest::perseRequestMessage()
{
	char *line;

	line = strtok(_request_message, "\n");
	printf("%s\n", line);

	_method = strtok(line, " ");
	if (_method == NULL) {
		printf("get method error\n");
		return -1;
	}

	_uri = strtok(NULL, " ");
	if (_uri == NULL) {
		printf("get method error\n");
		return -1;
	}

	_protocol_version = strtok(NULL, " ");
	if (_protocol_version	== NULL) {
		printf("get method error\n");
		return -1;
	}

	//ちゃんと入っているか確認
	/* printf("%s\n", _method); */
	/* printf("%s\n", _uri); */
	/* printf("%s\n", _protocol_version); */

	return 0;
}

void HTTPRequest::set_uri(char * new_uri) {
	_uri = strdup(new_uri);	
}

void HTTPRequest::show()
{
	printf("req_mes: %s\n", _request_message);
	printf("req_size: %d\n", _request_size);
	printf("ws: %d\n", _ws);
	printf("method: %s\n", _method);
	printf("uri: %s\n", _uri);
	printf("protocol_version: %s\n", _protocol_version);

}

char *HTTPRequest::get_request_message()
{
	return _request_message;
}

char *HTTPRequest::get_method()
{
	return _method;
}

char *HTTPRequest::get_uri() {
	return _uri;
}

char *HTTPRequest::get_protocol_version() {
	return _protocol_version;
}

int HTTPRequest::get_ws() {
	return _ws;
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
