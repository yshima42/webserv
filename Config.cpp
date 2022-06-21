#include "Config.hpp"

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

void Config::parse_config(std::string file)
{
	std::string file_content;

	file_content = read_file(file);

	//file_content = ;

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
