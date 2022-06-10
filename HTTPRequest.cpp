#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest()
{

}

HTTPRequest::~HTTPRequest()
{
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
