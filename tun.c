#include <stdio.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <arpa/inet.h>

int tun_alloc(char *dev) {

	struct ifreq ifr;
	int fd, err;
	char *clonedev = "/dev/net/tun";

	if( (fd = open(clonedev, O_RDWR)) < 0 ) {
		return fd;
	}

	memset(&ifr, 0, sizeof(ifr));
	ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
	if (dev[0]!='\0') {
		strncpy(ifr.ifr_name, dev, IFNAMSIZ);
	}

	if ( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ) {
		close(fd);
		return err;
	}

	strcpy(dev, ifr.ifr_name);

	return fd;
}

