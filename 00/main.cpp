#include "ServerSocket.hpp"


int main() {
	ServerSocket s("4242");

	s.AcceptLoopSelect();
	s.shutdown();
	s.close();
}
