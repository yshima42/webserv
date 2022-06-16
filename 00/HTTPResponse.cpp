#include "HTTPResponse.hpp"
#include "HTTPRequest.hpp"

unsigned int getFileSize(const char *path) {
    int size, read_size;
    char read_buf[SIZE];
    FILE *f;

    f = fopen(path, "rb");
    if (f == NULL) {
        return 0;
    }

    size = 0;
    do {
        read_size = fread(read_buf, 1, SIZE, f);
        size += read_size;
    } while(read_size != 0);

    fclose(f);

    return size;
}

int getProcessing(char *body, char *file_path) {

    FILE *f;
    int file_size;

    file_size = getFileSize(file_path);
    if (file_size == 0) {
        printf("getFileSize error\n");
        return 404;
    }

    f = fopen(file_path, "r");
    fread(body, 1, file_size, f);
    fclose(f);

    return 200;
}

HTTPResponse::HTTPResponse(HTTPRequest *req)
	:_ws(req->get_ws()), _method(req->get_method()), _uri(req->get_uri()), _protocol_version(req->get_protocol_version())
{
	if (strcmp(req->get_method(), "GET") == 0) {
    	if (strcmp(req->get_uri(), "/") == 0) {
        	/* /が指定された時は/index.htmlに置き換える */
			req->set_uri((char *)"./index.html");
            //strcpy(target, "/index.html");
        }
		status = getProcessing(body, req->get_uri());
        } else {
            status = 404;
	}
    
}

HTTPResponse::~HTTPResponse()
{
}

HTTPResponse::HTTPResponse(HTTPResponse const &other)
{
    *this = other;
}

HTTPResponse &HTTPResponse::operator=(HTTPResponse const &other)
{
    if (this != &other)
    {
    }
    return *this;
}
