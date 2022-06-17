#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP

class HTTPResponse
{
    public:
        HTTPResponse();
        virtual ~HTTPResponse();
        HTTPResponse(HTTPResponse const &other);
        HTTPResponse &operator=(HTTPResponse const &other);

    private:
};

#endif
