#include <sys/socket.h>
#define ORBIS
#ifdef ORBIS
int sceNetRecv(int,void *buf,size_t len, int flags);
#endif
ssize_t recv(int fd, void *buf, size_t len, int flags)
{
	#ifdef ORBIS
	return sceNetRecv(fd, buf, len, flags);
	#else
	return recvfrom(fd, buf, len, flags, 0, 0);
	#endif
}
