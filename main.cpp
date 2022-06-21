#include "HTTPRequest.hpp"
#include "HTTPServer.hpp"
#include "Webserv.hpp"
#include "Config.hpp"

int main(int ac, char *av[]) {
	Config config;

	if (ac != 2) {
		std::cerr << "Usage: ./webserv <config file>" << std::endl;
		return 0;
	}
	//try chatchやる
	config = Config(av[1]);

  /* Webserv s("4242"); */

  /* s.loop(); */
  /* s.shutdown(); */
  /* s.close(); */
}
