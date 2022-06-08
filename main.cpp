#include "ServerSocket.hpp"



int main() {
	ServerSocket s("4242");

	AcceptLoop(s.getSock());
	s.shutdown();
	s.close();
}
