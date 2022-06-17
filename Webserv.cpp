#include "Webserv.hpp"
#include "Request.hpp"
#include "Server.hpp"

Webserv::Webserv(std::string port)
{
	int portno, opt;
	struct servent *se;
	struct sockaddr_in my;

	//clients配列初期化
	for (int i = 0; i < MAX_CLIENTS; i++) {
		clients[i] = 0;
	}

	memset((char *)&my, 0, sizeof(my));
	my.sin_family = AF_INET;
	my.sin_addr.s_addr = htonl(INADDR_ANY);

	if (isdigit(portnm[0])) {
		if ((portno = stoi(portnm)) <= 0) {
			fprintf(stderr, "bad port no\n");
		}
		my.sin_port = htons(portno);
	} else {
		if ((se = getservbyname(portnm.c_str(), "tcp")) == NULL) {
			fprintf(stderr, "getservbyname():error\n");
		} else {
			my.sin_port = se->s_port;
		}
	}

	fprintf(stderr, "port=%d\n", ntohs(my.sin_port));
	
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
	}

	opt = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(int)) != 0) {
		perror("setsoctopt");
		::close (sock);
	}

	if (::bind(sock, (struct sockaddr *)&my, sizeof(my)) == -1) {
		perror("bind");
		::close(sock);
	}

	if (::listen(sock, SOMAXCONN) == -1) {
		perror("listen");
		::close(sock);
	}
}

Webserv::~Webserv()
{
}

void Webserv::run()
{
	fd_set readfds;
	int maxfd = _sock;
	int i, count = 0;
	int ret = 0;

	while (1)	
	{
		FD_ZERO(&readfds);
		FD_SET(_sock, &readfds);

		//つながっているクライアントからの発言を見張る
		for (i = 0; i < clients_no; i++) {
			FD_SET(clients[i], &readfds);
			if (clients[i] > maxfd) {
				maxfd = clients[i];
				count++;
			}
		}
		fprintf(stderr, "<< clients count: %d >>\n", count);
		
		if (select(maxfd + 1, (fd_set *)&readfds, NULL, NULL, NULL) < 0) {
			perror("select");
			exit(1); // 要検討
		}

		//新しい接続か
		int acc;
		if (FD_ISSET(_sock, &readfds)) {
			struct sockaddr_in from;
			socklen_t len = sizeof(from);
			if ((acc = accept(_sock, (struct sockaddr *)&from, &len)) == -1) {
				perror("accept");
				//continue; //必要？
			}
			if (clients_no >= MAX_CLIENTS) {
				write(acc, "too mamy\n", 9);
				::shutdown(acc, SHUT_RDWR);
				::close(acc);
				fprintf(stderr, "Refused a new connection.\n");
			} else {
				clients[clients_no] = acc;
				clients_no++;
				fprintf(stderr, "accepted a connection on descriptor %d.\n", acc);
			}
		}
		for (i = 0; i < clients_no; i++) {
			if (FD_ISSET(clients[i], &readfds)) {
				ret = _server.recv(clients[i]);
				if (ret <= 0) {
					//エラーまたは切断
					close(clients[i]);
					clients[i] = 0;
				}
			}
		}
	}
}


Webserv::Webserv(Webserv const &other)
{
    *this = other;
}

Webserv &Webserv::operator=(Webserv const &other)
{
    if (this != &other)
    {
    }
    return *this;
}
