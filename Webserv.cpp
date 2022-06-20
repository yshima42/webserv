#include "Webserv.hpp"

Webserv::Webserv(std::string port)
    : address_("127.0.0.1"), port_(port), clients_no_(0) {
  // clients配列初期化
  for (int i = 0; i < MAX_CLIENTS; i++) {
    clients_[i] = -1;
  }

  int portno, opt = 1;
  struct servent *se;
  struct sockaddr_in sa;

  // socket用初期化
  memset((char *)&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = htonl(INADDR_ANY);

  // portが数字かどうか確認
  if (isdigit(port_[0])) {
    if ((portno = stoi(port)) <= 0) {
      fprintf(stderr, "bad port no\n");
    }
    sa.sin_port = htons(portno);
  } else {
    //数字じゃなかったらドメイン確認
    if ((se = getservbyname(port.c_str(), "tcp")) == NULL) {
      fprintf(stderr, "getservbyname():error\n");
    } else {
      sa.sin_port = se->s_port;
    }
  }

  //受け取ったport表示
  std::cout << "port = " << ntohs(sa.sin_port) << std::endl;

  if ((sock_ = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
  }

  if (setsockopt(sock_, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(int)) !=
      0) {
    perror("setsockopt");
    ::close(sock_);
  }

  if (::bind(sock_, (struct sockaddr *)&sa, sizeof(sa)) == -1) {
    perror("bind");
    ::close(sock_);
  }

  // TODO:SOMAXCONNのマクロの値確認
  if (::listen(sock_, SOMAXCONN) == -1) {
    perror("listen");
    ::close(sock_);
  }
}

Webserv::~Webserv() {}

// select, acceptをしてaccepted fdをServerクラスにつなぐ
void Webserv::loop() {
  fd_set readfds;
  int maxfd = sock_ + 1;
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

    //いずれかの記述子の準備ができるまで待つ
    if (select(maxfd, (fd_set *)&readfds, NULL, NULL, NULL) < 0) {
      perror("select");
      exit(1);  //要検討
    }

    //新しい接続かどうか
    if (FD_ISSET(sock_, &readfds)) {
      struct sockaddr_in ca;  // client側
      socklen_t ca_len = sizeof(ca);
      int acc;

      if ((acc = accept(sock_, (struct sockaddr *)&ca, &ca_len)) == -1) {
        perror("accept");
      }
      if (clients_no_ >= MAX_CLIENTS) {
        write(acc, "too many\n", 9);  // 後ほど変更
        ::shutdown(acc, SHUT_RDWR);
        ::close(acc);
        fprintf(stderr, "Refused a new connection.\n");  //後ほど変更
      } else {
        printf("clients = acc\n");
        clients_[clients_no_] = acc;
        clients_no_++;
        fprintf(stderr, "accepted a connection on descriptor %d.\n", acc);
      }
    }

    for (i = 0; i < clients_no_; i++) {
      if (FD_ISSET(clients_[i], &readfds)) {
        //ここからServerにつなげる
        Server server(clients_[i]);
        int ret = server.run();
        if (ret <= 0) {
          ::close(clients_[i]);
          clients_[i] = -1;
        }
      }
    }
  }
}

int Webserv::shutdown() {
  int status = ::shutdown(sock_, SHUT_RDWR);
  std::cout << "shuddown" << std::endl;
  if (status == -1) {
    perror("shutdown");
    exit(EXIT_FAILURE);
  }
  return status;
}

void Webserv::close() {
  ::close(sock_);
  std::cout << "closed" << std::endl;
}

Webserv::Webserv(Webserv const &other) { *this = other; }

Webserv &Webserv::operator=(Webserv const &other) {
  if (this != &other) {
  }
  return *this;
}
