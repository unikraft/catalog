/*
 * epoll wrapper functions
 *
 * 2011, Operating Systems
 */

#ifndef TESTS_OS_DEMO_SERVER_W_EPOLL_H_
#define TESTS_OS_DEMO_SERVER_W_EPOLL_H_	1

#ifdef __cplusplus
extern "C" {
#endif


#define EPOLL_TIMEOUT_INFINITE		-1


static inline int w_epoll_create(void)
{
	return epoll_create(10);
}

static inline int w_epoll_add_fd_in(int epollfd, int fd)
{
	struct epoll_event ev;

	ev.events = EPOLLIN;
	ev.data.fd = fd;

	return epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

static inline int w_epoll_add_fd_out(int epollfd, int fd)
{
	struct epoll_event ev;

	ev.events = EPOLLOUT;
	ev.data.fd = fd;

	return epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

static inline int w_epoll_add_fd_inout(int epollfd, int fd)
{
	struct epoll_event ev;

	ev.events = EPOLLIN | EPOLLOUT;
	ev.data.fd = fd;

	return epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

static inline int w_epoll_update_fd_in(int epollfd, int fd)
{
	struct epoll_event ev;

	ev.events = EPOLLIN;
	ev.data.fd = fd;

	return epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

static inline int w_epoll_update_fd_out(int epollfd, int fd)
{
	struct epoll_event ev;

	ev.events = EPOLLOUT;
	ev.data.fd = fd;

	return epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

static inline int w_epoll_update_fd_inout(int epollfd, int fd)
{
	struct epoll_event ev;

	ev.events = EPOLLIN | EPOLLOUT;
	ev.data.fd = fd;

	return epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

static inline int w_epoll_remove_fd(int epollfd, int fd)
{
	struct epoll_event ev;

	/*
	 * ev needn't be initialized
	 * It has to be passed to epoll as a non-NULL argument for
	 * pre-2.6.9 kernels.
	 */
	ev.events = EPOLLIN;
	ev.data.fd = fd;

	return epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

static inline int w_epoll_add_ptr_in(int epollfd, int fd, void *ptr)
{
	struct epoll_event ev;

	ev.events = EPOLLIN;
	ev.data.ptr = ptr;

	return epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

static inline int w_epoll_add_ptr_out(int epollfd, int fd, void *ptr)
{
	struct epoll_event ev;

	ev.events = EPOLLOUT;
	ev.data.ptr = ptr;

	return epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

static inline int w_epoll_add_ptr_inout(int epollfd, int fd, void *ptr)
{
	struct epoll_event ev;

	ev.events = EPOLLIN | EPOLLOUT;
	ev.data.ptr = ptr;

	return epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

static inline int w_epoll_update_ptr_in(int epollfd, int fd, void *ptr)
{
	struct epoll_event ev;

	ev.events = EPOLLIN;
	ev.data.ptr = ptr;

	return epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

static inline int w_epoll_update_ptr_out(int epollfd, int fd, void *ptr)
{
	struct epoll_event ev;

	ev.events = EPOLLOUT;
	ev.data.ptr = ptr;

	return epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

static inline int w_epoll_update_ptr_inout(int epollfd, int fd, void *ptr)
{
	struct epoll_event ev;

	ev.events = EPOLLIN | EPOLLOUT;
	ev.data.ptr = ptr;

	return epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

static inline int w_epoll_remove_ptr(int epollfd, int fd, void *ptr)
{
	struct epoll_event ev;

	/*
	 * ev needn't be initialized
	 * It has to be passed to epoll as a non-NULL argument for
	 * pre-2.6.9 kernels.
	 */
	ev.events = EPOLLIN;
	ev.data.ptr = ptr;

	return epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

static inline int w_epoll_wait_infinite(int epollfd, struct epoll_event *rev)
{
	return epoll_wait(epollfd, rev, 1, EPOLL_TIMEOUT_INFINITE);
}
#ifdef __cplusplus
}
#endif

#endif  // TESTS_OS_DEMO_SERVER_W_EPOLL_H_
