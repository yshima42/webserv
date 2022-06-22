#ifndef CONFIG_HPP
# define CONFIG_HPP

#include "Server.hpp"
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sstream>
#include <vector>

#define BUFFER_SIZE 128

class Config
{
    public:
        Config();
        Config(std::string file);
        virtual ~Config();
        Config(Config const &other);
        Config &operator=(Config const &other);

		void parse_config(std::string file);

    private:
		std::vector< Server > servers_;

};

#endif
