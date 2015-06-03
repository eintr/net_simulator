#ifndef WORMHOLE_MSG_H
#define WORMHOLE_MSG_H

#include "wormhole_protocol.h"

struct internal_frame_st {
	uint64_t conn_id;
	uint8_t code;
	struct fec_info_st fec_info;
	union {
		struct {
			uint32_t server_tun_addr;
			uint32_t client_tun_addr;
			uint32_t route_prefixes[];
		} config_ipv4;
		struct {
			uint64_t conn_id;
		} chap_connect;
		struct {
			uint64_t ping_timestamp_ms;
			uint64_t pong_timestamp_ms;
		} echo;
		struct {
			uint8_t data[0];
		} data;
		struct {
			uint8_t salt[SALT_LENGTH];
			uint8_t md5[MD5_DIGEST_LENGTH];
			uint8_t client_id[1];
		} chap;
		struct {
			uint8_t reason[1];
		} chap_reject;
	};
};

int msg_decode(char *data, size_t datalen, struct internal_frame_st *dst);
int msg_encode(struct internal_frame_st *src, char *data, size_t *datalen);

#endif

