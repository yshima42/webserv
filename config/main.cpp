#include "ConfigParser.hpp"

int main(int ac, char *av[]) {
	if (ac != 2) {
		std::cerr << "Usage: ./webserv <config file>" << std::endl;
		return 0;
	}
	try {
		ConfigParser configparser(av[1]);
		//ServerConfig serverconfig = configparser.getServerConfigs();

	} catch (...) {
		std::cout << "something is wrong" << std::endl;

	}

  /* Webserv s("4242"); */

  /* s.loop(); */
  /* s.shutdown(); */
  /* s.close(); */
}
