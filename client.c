#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include "cJSON.h"
#include "client.h"
#include "client_conn.h"
#include "wormhole_protocol.h"

static struct client_conn_st conn;

static int shell(const char *cmd)
{
	int ret;

	printf("run: %s  ...  ", cmd);
	ret = system(cmd);
	if (ret==-1) {
		printf("failed: %m.\n");
	} else {
		printf("status=%d.\n", ret);
	}
	return ret;
}

static int client_chap(int sd, cJSON *conf)
{

}

static int client_conn_init(cJSON *conf)
{
	int err;
	struct addrinfo hint, *result;
	char *serveraddr, *serverport, *clientport;
	struct sockaddr *curr;
	struct sockaddr_in clientaddr;

	memset(&conn, 0, sizeof(conn));

	serveraddr = conf_get_str("ServerAddress", conf);
	if (serveraddr==NULL) {
		fprintf(stderr, "ServerAddress not defined!\n");
		return -1;
	}
	serverport = conf_get_str("ServerPort", conf);
	if (serverport==NULL) {
		fprintf(stderr, "ServerPort not defined!\n");
		return -1;
	}
	hint.ai_flags = 0;
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_DGRAM;
	hint.ai_protocol = 0;
	err = getaddrinfo(serveraddr, serverport, &hint, &result);
	if (err) {
		fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(err));
		return -1;
	}

	conn.sd = socket(hint.ai_family, hint.ai_socktype, hint.ai_protocol);
	if (conn.sd<0) {
		perror("socket()");
		abort();
	}

	clientport = conf_get_str("ClientPort", conf);
	if (clientport!=NULL) {
		clientaddr.sin_family = AF_INET;
		clientaddr.sin_addr.s_addr = 0;
		clientaddr.sin_port = htons(strtol(clientport, NULL, 10));
		if (bind(conn.sd, (void*)&clientaddr, sizeof(clientaddr))<0) {
			perror("bind()");
		}
	}

	conn.nr_peer = 0;
	for (curr=result->ai_addr; curr!=NULL; curr=curr->ai_next) {
		conn.nr_peer++;
	}
	conn.peer = malloc(sizeof(struct sockaddr_storage)*conn.nr_peer);
	for (i=0,curr=result->ai_addr; curr!=NULL; curr=curr->ai_next) {
		memcpy(conn.peer[i], curr->ai_addr, curr->ai_addrlen);
	}

	conn.tun_fd = tun_alloc(conn.tun_name);
	if (conn.tun_fd<0) {
		perror("tun_alloc()");
		abort();
	}

	return 0;
}

static tun_config()
{
	char cmdline[BUFSIZE];

	snprintf(cmdline, BUFSIZE, "ip addr add dev %s %s peer %s", tun_name, tun_local_addr, tun_peer_addr);
	shell(cmdline);
	snprintf(cmdline, BUFSIZE, "ip link set dev %s up", tun_name);
	shell(cmdline);
}

static int client_conn_chap(cJSON *conf)
{
}

void client(cJSON *conf)
{
	if (client_conn_init(conf)!=0) {
		return -1;
	}
}

