#include "ServerSocket.hpp"
#include <cstdlib>

ServerSocket::ServerSocket()
	: address("127.0.0.1"), port("4242")
{
}

ServerSocket::ServerSocket(std::string portnm)
	:address("127.0.0.1"), port(portnm)
{
	int portno, opt;
	struct servent *se;
	struct sockaddr_in my;

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

int SendRecvLoop(int acc)
{
	char buf[512], *ptr;
	int len;

	while (1) {
		if ((len = recv(acc, buf, sizeof(buf), 0)) < 0) {
				perror("recv");
				break;
		}
		if (len == 0) {
			fprintf(stderr, "recv:EOF\n");
			break;
		}

		buf[len] = '\n';
		if ((ptr = strpbrk(buf, "\r\n")) != NULL) {
			*ptr = '\0';
		}

		fprintf(stderr, "[client]%s\n", buf);

		strcat(buf, ":OK\r\n");
		len = strlen(buf);

		if ((len = send(acc, buf, len, 0)) < 0) {
				perror("send");
				break;
		}
	}
	return 0;
}

int AcceptLoop(int soc)
{
	int acc;
	socklen_t len;
	struct sockaddr_in from;

	while (1) {
		len = sizeof(from);

		acc = accept(soc, (struct sockaddr *)&from, &len);
		if (acc < 0) {
			if (errno != EINTR) {
				perror("accept");
			}
		} else {
			fprintf(stderr, "accept:%s:%d\n", inet_ntoa(from.sin_addr), ntohs(from.sin_port));
			SendRecvLoop(acc);

			close(acc);
			acc = 0;
		}
	}
	return (0);
}

ServerSocket::ServerSocket(int domain, int type, int protocol)
	: address("127.0.0.1"), port("4242")
{
	int soval = 1;
	memset(&sa, 0, sizeof(sa));
	sock = socket(domain, type, protocol);
	if (sock < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	//アドレス再利用の設定
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
}

int ServerSocket::bind(std::string ip, std::string port)
{
	memset(&sa, 0, sizeof(sa));
	sa.sin_len = sizeof(sa);
	sa.sin_family = AF_INET;
	sa.sin_port = htons(stoi(port));
	sa.sin_addr.s_addr = htonl(INADDR_ANY);

	int status = ::bind(sock, (struct sockaddr *)&sa, sizeof(sa));
	if (status == -1) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
	return status;
}

int ServerSocket::listen(int max_queue)
{
	int status = ::listen(sock, max_queue);
	if (status < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	return status;
}

//int ServerSocket::connect(std::string ip, std::string port){}

int ServerSocket::accept()
{
	struct sockaddr_in ca;
	socklen_t ca_len;
	int ws;

	ca_len = sizeof(ca);
	ws = ::accept(sock, (struct sockaddr *)&ca, &ca_len);
	if (ws == -1) {
		perror("accept");
	}
	return ws;
}

int ServerSocket::shutdown()
{
	int status = ::shutdown(sock, SHUT_RDWR);
	if (status == -1) {
		perror("shutdown");
		exit(EXIT_FAILURE);
	}
	return status;
}

void ServerSocket::close()
{
	::close(sock);
}

int ServerSocket::getSock()
{
	return sock;
}

ServerSocket::~ServerSocket()
{
}

ServerSocket::ServerSocket(ServerSocket const &other)
{
    *this = other;
}

ServerSocket &ServerSocket::operator=(ServerSocket const &other)
{
    if (this != &other)
    {
    }
    return *this;
}
