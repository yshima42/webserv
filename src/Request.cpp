#include "Request.hpp"

Request::Request(std::string & request_message)
	: method_(""), path_(""), protocol_(""), body_(""), port_(4242)
{
	(void)port_;
	this->parse(request_message);	
}

Request::~Request()
{
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (getline(ss, item, delim)) {
		if (!item.empty()) {
			elems.push_back(item);
		}
	}
	return elems;
}

void print_vec(std::vector<std::string> vec)
{
	std::vector<std::string>::iterator it = vec.begin();
	std::vector<std::string>::iterator ite = vec.end();
	for (;it < ite; it++) {
		std::cout << *it << std::endl;
	}
}

void Request::parse(std::string & request_message)
{
	std::vector<std::string> lines;

	lines = split(request_message, '\n');

	print_vec(lines);
	


}

Request::Request(Request const &other)
{
    *this = other;
}

Request &Request::operator=(Request const &other)
{
    if (this != &other)
    {
    }
    return *this;
}
