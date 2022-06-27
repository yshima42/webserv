#ifndef REQUEST_HPP
# define REQUEST_HPP

#include <iostream>
#include <map>
#include <iterator>
#include <vector>
#include <sstream>

class Request
{
    public:
        Request(std::string & request_message);
        virtual ~Request();
        Request(Request const &other);
        Request &operator=(Request const &other);

        void parse(std::string & request_message);

    private:
		std::string	method_;
		std::string path_;
		std::string protocol_;
		std::map<std::string, std::string> headers_;
		std::string body_;
		int port_;

};

#endif
