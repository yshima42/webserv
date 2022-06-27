#include "Config.hpp"
#include <cctype>

Config::Config()
{
}

Config::Config(std::string file)
{
	parse_config(file);
}

Config::~Config()
{
}

std::string read_file(std::string file) {
	std::string file_content;
	char buf[BUFFER_SIZE + 1] = {0};
	ssize_t cc;

	int fd = open(file.c_str(), O_RDONLY);
	if (fd < 0) {
		perror("open");
		exit(1);
	}
	while ((cc = read(fd, buf, sizeof(buf))) > 0) {
		file_content += buf;

		//buf初期化
		for (int i = 0; i < BUFFER_SIZE; i++)
			buf[i] = '\0';
	}
	close(fd);
	return file_content;
}

size_t count_lines(std::string str)
{
	size_t line_num = 0;

	for (size_t i = 0; str[i]; i++) {
		if (str[i] == '\n')
			line_num++;
	}
	return line_num;
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

template <typename T>
void print_vector(std::vector< T > vec) {
	typename std::vector< T >::iterator it = vec.begin();
	int i = 0;
	for(;it < vec.end(); it++) {
		i++;
		std::cout << i << "] " << *it << std::endl;
	}
}

char char_after_spaces(std::string str) {
	for (int i = 0; str.at(i); i++) {
		if (!(std::isspace(str.at(i)) && str.at(i) != '\n'))
			return str.at(i);
	}
	return '\0';
}

// スペースと改行だけの行、コメント行をvectorからdelete
// スペースと改行だけの時にエラー isspaceの部分見直し
void del_skip_lines(std::vector<std::string> &vec) {
	std::vector<std::string>::iterator it = vec.begin();
	for(; it < vec.end(); it++) {
		if (char_after_spaces(*it) == '\n' || char_after_spaces(*it) == '#')
			vec.erase(it);
	}
}

void Config::parse_config(std::string file)
{
	//size_t i = 0;
	std::string file_content = read_file(file);
	//size_t line_num = count_lines(file_content);
	std::vector<std::string> lines = split(file_content, '\n');
	//std::string a = "     \n";
	//std::cout << char_after_spaces(a) << std::endl;
	del_skip_lines(lines);
	print_vector(lines);
	/* while (i < line_num) */
	/* { */
	/* 		std::cout << lines[i] << std::endl; */
	/* 	i++; */
	/* } */


}

Config::Config(Config const &other)
{
    *this = other;
}

Config &Config::operator=(Config const &other)
{
    if (this != &other)
    {
    }
    return *this;
}
