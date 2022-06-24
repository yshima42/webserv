#ifndef ECHOSERVER_SRC_SELECTOR_HPP_
#define ECHOSERVER_SRC_SELECTOR_HPP_

#include <sys/select.h>
#include <time.h>

#include <iostream>
#include <set>

class Selector {
 public:
  explicit Selector(std::set<int> readfds);
  ~Selector();

  void init(std::set<int> readfds);
  int monitor();
  void addTargetReadFd(int fd);
  void addTargetWriteFd(int fd);
  void removeTargetReadFd(int fd);
  void removeTargetWriteFd(int fd);

  // アクセッサー
  int getEventCount() const;
  const std::set<int>& getReadyReadFds() const;
  const std::set<int>& getReadyWriteFds() const;
  // デバッグ用
  void showDebugInfo() const;

 private:
  static const int kTimeoutSec = 5;

  // not use
  Selector();
  Selector(const Selector& other);
  Selector& operator=(const Selector& other);

  fd_set toFdset(std::set<int> cont_fds);
  std::set<int> toSet(fd_set fds, std::set<int> cont_fds);

  int evnet_cnt_;
  int max_targetfd_;
  int max_target_readfd_;
  int max_target_writefd_;
  struct timeval timeout_;
  std::set<int> target_readfds_;
  std::set<int> target_writefds_;
  std::set<int> ready_readfds_;
  std::set<int> ready_writefds_;
};

#endif  // ECHOSERVER_SRC_SELECTOR_HPP_
