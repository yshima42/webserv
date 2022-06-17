#include "Request.hpp"
#include "Server.hpp"
#include "Webserv.hpp"

int main(int ac, char *av[]) {
	if (ac != 2)
		std::cout << "wrong" << std::endl;

	Webserv ws(av[1]);
	ws.run();
	//int ac_sock;

	/* while (1) { */
	/* 	//ac_sock = s.AcceptSelect(); */
	/* 	if (ac_sock == 0) // 要検討 */
	/* 		continue; */
	/* 	HTTPRequest req(ac_sock); */
	/* 	req.recvRequestMessage(); */
	/* } */
	//s.shutdown();
	//s.close();

}
