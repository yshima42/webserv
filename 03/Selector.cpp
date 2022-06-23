#include "Selector.hpp"

Selector::Selector(std::set<int> readfds)
{
	init(readfds);
	max_target_writefd_ = -1;
}

Selector::~Selector()
{
}

void Selector::init(std::set<int> readfds) {
	target_readfds_ = readfds;

	std::set<int>::iterator ite = target_readfds_.end();
	ite--;
	max_target_readfd_ = *ite;
	max_targetfd_ = *ite;

	event_cnt_ = 0;
	timeout_.tv_sec = kTimeoutSec;
	timeout_.tv_usec = 0;
}

int Selector::monitor() {
	fd_set tmp_readfds = toFdset(target_readfds_);
	fd_set tmp_writefds = toFdset(target_writefds_);

	event_cnt_ = select(max_targetfd_ + 1, &tmp_readfds, &tmp_writefds, NULL, &timeout_);

	if (event_cnt_ < 0) {
		throw std::runtime_error("select() failed");
	}
	if (event_cnt_ == 0) {
		std::cerr << "Time out" << std::endl;
	}
	ready_readfds_ = toSet(tmp_readfds, target_readfds_);
	ready_writefds_ = toSet(tmp_writefds, target_writefds_);
	return event_cnt_;
}

int Selector::getEventCount() const { return event_cnt_; }

const std::set<int>& Selector::getReadyReadFds() const {
	return ready_readfds_;
}

const std::set<int>& Selector::getReadyWriteFds() const {
	return ready_writefds_;
}

void Selector::addTargetReadFd(int fd) {
	target_readfds_.insert(fd);
	if (fd > max_target_readfd_) {
		max_target_readfd_ = fd;
	}
	if (fd > max_targetfd_) {
		max_targetfd_ = fd;
	}
}

void Selector::addTargetWriteFd(int fd) {
  target_writefds_.insert(fd);
  if (fd > max_target_writefd_) {
    max_target_writefd_ = fd;
  }
  if (fd > max_targetfd_) {
    max_targetfd_ = fd;
  }
}

void Selector::removeTargetReadFd(int fd) {
	target_readfds_.erase(fd);
	if (target_readfds_.size() == 0) {
		max_target_readfd_ = -1;
	} else {
		if (fd == max_target_readfd_) {
			std::set<int>::iterator itr = target_readfds_.end();
			itr--;
			max_target_readfd_ = *itr;
		}
	}
	max_targetfd_ = (max_target_readfd_ > max_target_writefd_)
					? max_target_readfd_
					: max_target_writefd_;
}

void Selector::removeTargetWriteFd(int fd) {
  target_writefds_.erase(fd);
  if (target_writefds_.size() == 0) {
    max_target_writefd_ = -1;
  } else {
    if (fd == max_target_writefd_) {
      std::set<int>::iterator itr = target_writefds_.end();
      itr--;
      max_target_writefd_ = *itr;
    }
  }
  max_targetfd_ = (max_target_readfd_ > max_target_writefd_)
                      ? max_target_readfd_
                      : max_target_writefd_;
}

fd_set Selector::toFdset(std::set<int> cont_fds) {
	fd_set fds;
	
	FD_ZERO(&fds);
	if (cont_fds.size() == 0) {
		return fds;
	}
	std::set<int>::iterator it = cont_fds.begin();
	std::set<int>::iterator ite = cont_fds.end();
	for (; it != ite; it++) {
		FD_SET(*it, &fds);
	}
	return fds;
}

std::set<int> Selector::toSet(fd_set fds, std::set<int> cont_fds) {
	std::set<int> new_cont_fds;

	std::set<int>::iterator it = cont_fds.begin();
	std::set<int>::iterator ite = cont_fds.end();
	for (; it != ite; it++) {
		if (FD_ISSET(*it, &fds)) {
			new_cont_fds.insert(*it);
		}
	}
	return new_cont_fds;
}

void printSetInfo(std::set<int> fds) {
	std::set<int>::iterator it = fds.begin();
  std::set<int>::iterator ite = fds.end();

  std::cerr << "size[" << fds.size() << "] ";
  for (; it != ite; it++) {
    std::cerr << *it << ", ";
  }
  std::cerr << std::endl;
}

void Selector::showDebugInfo() const {
  std::cerr << std::endl;
  std::cerr << "###Selecter Info###" << std::endl
            << "max_fd : " << max_targetfd_ << std::endl
            << "max_rfd: " << max_target_readfd_ << std::endl
            << "max_wfd: " << max_target_writefd_ << std::endl
            << "evnet_cnt: " << event_cnt_ << std::endl;
  std::cerr << "target_readfds : ";
  printSetInfo(target_readfds_);
  std::cerr << "ready_readfds  : ";
  printSetInfo(ready_readfds_);
  std::cerr << "target_writefds: ";
  printSetInfo(target_writefds_);
  std::cerr << "ready_writefds : ";
  printSetInfo(ready_writefds_);
  std::cerr << "###end###" << std::endl;
  std::cerr << std::endl;
}

Selector::Selector(Selector const &other)
{
    *this = other;
}

Selector &Selector::operator=(Selector const &other)
{
    if (this != &other)
    {
    }
    return *this;
}
