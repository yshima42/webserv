#ifndef CONFIG_HPP
# define CONFIG_HPP

#include "ServerConfig.hpp"
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sstream>
#include <vector>
#include <cctype>
#include <fstream>

#define BUFFER_SIZE 128

// コンストラクタでparseはしてしまう
// parseメソッドで必要な情報を返す
class ConfigParser
{
    public:
        ConfigParser();
        ConfigParser(std::string file);
        virtual ~ConfigParser();
        ConfigParser(ConfigParser const &other);
        ConfigParser &operator=(ConfigParser const &other);

		std::vector<ServerConfig> getServerConfigs() const;

    private:
		std::vector< ServerConfig > serverconfigs_;
		

		//std::vector<std::string> tokenize(std::vector<std::string> file_content);
		void parse_file(std::string file);
		std::vector<std::string> read_file(std::string file);
		std::string read_file_(std::string file);
		size_t count_lines(std::string str);
		std::vector<std::string> split(const std::string &s, char delim);
		char char_after_spaces(std::string str);
		void parse_servers(std::vector<std::string> tokens);
		std::vector<std::string> isspace_split(std::string str);

};

#endif
