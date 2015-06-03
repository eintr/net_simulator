#ifndef CLIENT_CONN_H
#define CLIENT_CONN_H

#define	KEYSIZE	64

struct client_conn_st {
	uint64_t id;

	int sd;
	int nr_peer;
	struct sockaddr_storage *peer;

	int tun_fd;
	char tun_name[IFNAMSIZ];

	uint8_t shared_key[KEYSIZE];
};

#endif

