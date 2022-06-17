#include "HTTPRequest.hpp"
#include "ServerSocket.hpp"

int main() {
	ServerSocket s("4242");
	int ac_sock;

	while (1) {
		ac_sock = s.AcceptSelect();
		//printf("add=%d\n", ac_sock);
		if (ac_sock == 0) // 要検討
			continue;
		HTTPRequest req(ac_sock);
		req.recvRequestMessage();
	}
	s.shutdown();
	s.close();

}
