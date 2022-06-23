#ifndef SELECTOR_HPP
# define SELECTOR_HPP

#include <sys/select.h>
#include <time.h>
#include <iostream>
#include <set>

class Selector
{
    public:
        Selector(std::set<int> readfds);
        virtual ~Selector();

		void init(std::set<int> readfds);
		int monitor();
		void addTargetReadFd(int fd);
		void addTargetWriteFd(int fd);
		void removeTargetReadFd(int fd);
		void removeTargetWriteFd(int fd);

		int getEventCount() const;
		const std::set<int>& getReadyReadFds() const;
		const std::set<int>& getReadyWriteFds() const;
		
		//debug
		void showDebugInfo() const;

        Selector(Selector const &other);
        Selector &operator=(Selector const &other);

    private:
		static const int kTimeoutSec = 5;

		fd_set toFdset(std::set<int> cont_fds);
		std::set<int> toSet(fd_set fds, std::set<int> cont_fds);

		int event_cnt_;
		int max_targetfd_;
		int max_target_readfd_;
		int max_target_writefd_;
		struct timeval timeout_;
		std::set<int> target_readfds_;
		std::set<int> target_writefds_;
		std::set<int> ready_readfds_;
		std::set<int> ready_writefds_;
};

#endif
