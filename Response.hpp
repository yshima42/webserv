#ifndef RESPONSE_HPP
# define RESPONSE_HPP

class Response
{
    public:
        Response();
        virtual ~Response();
        Response(Response const &other);
        Response &operator=(Response const &other);

    private:
};

#endif
