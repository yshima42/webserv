#include "ConfigParser.hpp"

template <typename T>
void print_vector(std::vector< T > vec) {
	typename std::vector< T >::iterator it = vec.begin();
	int i = 0;
	for(;it < vec.end(); it++) {
		i++;
		std::cout << i << "] " << *it << std::endl;
	}
}

ConfigParser::ConfigParser()
{
}

ConfigParser::ConfigParser(std::string file)
{
	//std::vector<std::string> file_content = read_file(file);
	std::string file_content = read_file_(file);
	
	std::vector<std::string> tokens = isspace_split(file_content);
	print_vector(tokens);
}

std::vector<ServerConfig> ConfigParser::getServerConfigs() const
{
	return (serverconfigs_);
}

ConfigParser::~ConfigParser()
{
}

std::string ConfigParser::read_file_(std::string file) {
	std::stringstream ss;
	std::string buf;
	std::ifstream ifs(file);
	if (ifs.fail()) {
		throw -1;
	}
	while (getline(ifs, buf)) {
		ss << buf << "\n";
	}
	return ss.str();
}

size_t ConfigParser::count_lines(std::string str)
{
	size_t line_num = 0;

	for (size_t i = 0; str[i]; i++) {
		if (str[i] == '\n')
			line_num++;
	}
	return line_num;
}


std::vector<std::string> ConfigParser::split(const std::string &s, char delim) {
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

char ConfigParser::char_after_spaces(std::string str) {
	for (int i = 0; str.at(i); i++) {
		if (!(std::isspace(str.at(i)) && str.at(i) != '\n'))
			return str.at(i);
	}
	return '\0';
}

// スペースと改行だけの行、コメント行をvectorからdelete
// スペースと改行だけの時にエラー isspaceの部分見直し
/* void del_skip_lines(std::vector<std::string> &vec) { */
/* 	std::vector<std::string>::iterator it = vec.begin(); */
/* 	for(; it < vec.end(); it++) { */
/* 		if (char_after_spaces(*it) == '\n' || char_after_spaces(*it) == '#') */
/* 			vec.erase(it); */
/* 	} */
/* } */

//syamaさんのやり方 後ほどリファクター
std::vector<std::string> ConfigParser::isspace_split(std::string str) 
{
	std::vector<std::string> tokens;
	size_t i = 0;
	size_t j = 0;

	while (str[i]) {
		if (std::isspace(str[i])) {
			if (i == j)
				++j;
			else {
				tokens.push_back(std::string(str, j, i - j));
				j = i + 1;
			}
		}
		i++;
	}
	if (i != j)
		tokens.push_back(std::string(str, j, i - j));
	return tokens;
}

void ConfigParser::parse_servers(std::vector<std::string> tokens)
{
	std::vector<std::string>::iterator it = tokens.begin();
	std::vector<std::string>::iterator ite = tokens.end();
	for (; it < ite; it++) {
			if (tokens.size() > 0 && *it == "server" && *(it + 1) == "{") {
				std::cout << "OK" << std::endl;

		} else {
			std::cout << "something is wrong in config file" << std::endl;
			exit(1);
		}
	}
}
		
ConfigParser::ConfigParser(ConfigParser const &other)
{
    *this = other;
}

ConfigParser &ConfigParser::operator=(ConfigParser const &other)
{
    if (this != &other)
    {
    }
    return *this;
}
