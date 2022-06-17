#include "HTTPRequest.hpp"
#include "Server.hpp"
#include "Webserv.hpp"

int main() {
  Webserv s("4242");

  s.loop();
  s.shutdown();
  s.close();
}
