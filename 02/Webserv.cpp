#include "Webserv.hpp"
#include "Request.hpp"
#include "Server.hpp"

Webserv::Webserv(std::string port)
{
	Server server(port);
}

Webserv::~Webserv()
{
}

void Webserv::run()
{
	fd_set readfds;
	int maxfd = sock_;
	int i, count = 0;

	while (1) {

		FD_ZERO(&readfds);
		FD_SET(sock_, &readfds);

		//つながってるクライアントのbufに何か入っていないか見張る
		for (i = 0; i < clients_no_; i++) {
			if (clients_[i] != -1) {
				FD_SET(clients_[i], &readfds);
				if (clients_[i] + 1 > maxfd) {
					maxfd = clients_[i] + 1;
					count++;
				}
			}
		}
		//ここでタイムアウトのセットを行う必要あり

		//いずれかの記述子の準備ができるまで待つ
		if (select(maxfd, (fd_set *)&readfds, NULL, NULL, NULL) < 0) {
			perror("select");
			exit(1); //要検討
		}

		//新しい接続かどうか
		if (FD_ISSET(sock_, &readfds)) {
			struct sockaddr_in ca; // client側
			socklen_t ca_len = sizeof(ca);
			int acc;

			if ((acc = accept(sock_, (struct sockaddr *)&ca, &ca_len)) == -1) {
				perror("accept");
			}
			if (clients_no_ >= MAX_CLIENTS) {
				write(acc, "too many\n", 9); // 後ほど変更
				::shutdown(acc, SHUT_RDWR);
				::close(acc);
				fprintf(stderr, "Refused a new connection.\n"); //後ほど変更
			} else {
				clients_[clients_no_] = acc;
				clients_no_++;
				fprintf(stderr, "accepted a connection on descriptor %d.\n", acc);
			}
			for (i = 0; i < clients_no_; i++) {
				if (FD_ISSET(clients_[i], &readfds)) {
					int ret = server.run(clients_[i]); //ここからhttpServerにつなげる
					if (ret <= 0) {
						//エラーまたは切断
						close(clients_[i]);
						clients_[i] = -1;
					}
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
