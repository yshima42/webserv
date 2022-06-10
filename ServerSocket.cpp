#include "ServerSocket.hpp"
#include <cstdlib>

ServerSocket::ServerSocket(std::string portnm)
	:address("127.0.0.1"), port(portnm), clients_no(0)
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


void ServerSocket::delete_client(int ws) {
	int i;
	for (i = 0; i < clients_no; i++) {
		if (clients[i] == ws) {
			clients[i] = clients[clients_no -1];
			clients_no--;
			break;
		}
	}
}

#define SIZE 1024 * 5



int ServerSocket::createResponseMessage(int status, char *header, char *body, unsigned int body_size)
{
	unsigned int no_body_len;
	unsigned int body_len;
	
	response_message[0] = '\0';

    if (status == 200) {
        /* レスポンス行とヘッダーフィールドの文字列を作成 */
        sprintf(response_message, "HTTP/1.1 200 OK\r\n%s\r\n", header);

        no_body_len = strlen(response_message);
        body_len = body_size;
		printf("body_len: %d\n", body_len);

        /* ヘッダーフィールドの後ろにボディをコピー */
        memcpy(&response_message[no_body_len], body, body_len);
    } else if (status == 404) {
        /* レスポンス行とヘッダーフィールドの文字列を作成 */
        sprintf(response_message, "HTTP/1.1 404 Not Found\r\n%s\r\n", header);

        no_body_len = strlen(response_message);
        body_len = 0;
    } else {
        /* statusが200・404以外はこのプログラムで非サポート */
        printf("Not support status(%d)\n", status);
        return -1;
    }

    return no_body_len + body_len;
}


int ServerSocket::sendResponseMessage(int ws)
{
	send(ws, response_message, response_size, 0);
	return 0;
}


unsigned int getFileSize(const char *path) {
    int size, read_size;
    char read_buf[SIZE];
    FILE *f;

    f = fopen(path, "rb");
    if (f == NULL) {
        return 0;
    }

    size = 0;
    do {
        read_size = fread(read_buf, 1, SIZE, f);
        size += read_size;
    } while(read_size != 0);

    fclose(f);

    return size;
}

int getProcessing(char *body, char *file_path) {

    FILE *f;
    int file_size;

    file_size = getFileSize(file_path);
    if (file_size == 0) {
        printf("getFileSize error\n");
        return 404;
    }

    f = fopen(file_path, "r");
    fread(body, 1, file_size, f);
    fclose(f);

    return 200;
}

//ここがコネクタになる
void ServerSocket::httpServer(int ws)
{
	int status;
	HTTPRequest req(ws);
	char body[SIZE];
	char target[SIZE];
	unsigned int file_size;
	char header_field[SIZE];

	printf("ws: %d\n", req.get_ws());

	if (req.recvRequestMessage() == -1) {
		::shutdown(ws, SHUT_RDWR);
		::close(ws);
		delete_client(ws);
		fprintf(stderr, "connection closed on descriptor %d.\n", ws);
	}
	req.perseRequestMessage();

	strcpy(target, "./index.html");

	if (strcmp(req.get_method(), "GET") == 0) {
		status = getProcessing(body, target);
	} else {
		status = 400;
	}

	file_size = getFileSize(&target[1]);
	file_size = strlen(body);
	sprintf(header_field, "Content-Length: %u\r\n", file_size);

	printf("%s\n", response_message);
	response_size = createResponseMessage(status, header_field, body, file_size);
	printf("%s\n", response_message);
	sendResponseMessage(ws);

	//printf("%s", buf);
	//for (i = 0; i < clients_no; i++)
	//send(ws, buf, len, 0);
}


/* int httpServer(int soc) */
/* { */
/* 	char request_message[SIZE]; */
/* 	int request_size; */

/* 	while (1) { */

/* 		request_size = recvRequestMessage(soc, request_message, SIZE); */
/* 		if (request_size == -1) { */
/* 			printf("recvRequestMessage error\n"); */
/* 			break; */
/* 		} */
/* 		if (request_size == 0) { */
/* 			printf("connection ended\n"); */
/* 			break; */
/* 		} */
/* 		printf("%s", request_message); */
/* 	} */
/* 	return 0; */
/* } */


int ServerSocket::AcceptLoopSelect()
{
	fd_set readfds;
	int maxfd = sock;
	int i, count = 0;

	while (1) {
		FD_ZERO(&readfds);
		FD_SET(sock, &readfds);

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
		if (FD_ISSET(sock, &readfds)) {
			struct sockaddr_in from;
			socklen_t len = sizeof(from);
			if ((acc = accept(sock, (struct sockaddr *)&from, &len)) == -1) {
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
				httpServer(clients[i]);
				break;
			}
		}
	}

	return (0);
}

/* ServerSocket::ServerSocket(int domain, int type, int protocol) */
/* 	: address("127.0.0.1"), port("4242") */
/* { */
/* 	int soval = 1; */
/* 	memset(&sa, 0, sizeof(sa)); */
/* 	sock = socket(domain, type, protocol); */
/* 	if (sock < 0) { */
/* 		perror("socket"); */
/* 		exit(EXIT_FAILURE); */
/* 	} */

/* 	//アドレス再利用の設定 */
/* 	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1) { */
/* 		perror("setsockopt"); */
/* 		exit(EXIT_FAILURE); */
/* 	} */
/* } */

/* int ServerSocket::bind(std::string ip, std::string port) */
/* { */
/* 	(void)ip; */
/* 	memset(&sa, 0, sizeof(sa)); */
/* 	sa.sin_len = sizeof(sa); */
/* 	sa.sin_family = AF_INET; */
/* 	sa.sin_port = htons(stoi(port)); */
/* 	sa.sin_addr.s_addr = htonl(INADDR_ANY); */

/* 	int status = ::bind(sock, (struct sockaddr *)&sa, sizeof(sa)); */
/* 	if (status == -1) { */
/* 		perror("bind"); */
/* 		exit(EXIT_FAILURE); */
/* 	} */
/* 	return status; */
/* } */

/* int ServerSocket::listen(int max_queue) */
/* { */
/* 	int status = ::listen(sock, max_queue); */
/* 	if (status < 0) { */
/* 		perror("listen"); */
/* 		exit(EXIT_FAILURE); */
/* 	} */
/* 	return status; */
/* } */

//int ServerSocket::connect(std::string ip, std::string port){}

/* int ServerSocket::accept() */
/* { */
/* 	struct sockaddr_in ca; */
/* 	socklen_t ca_len; */
/* 	int ws; */

/* 	ca_len = sizeof(ca); */
/* 	ws = ::accept(sock, (struct sockaddr *)&ca, &ca_len); */
/* 	if (ws == -1) { */
/* 		perror("accept"); */
/* 	} */
/* 	return ws; */
/* } */

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
