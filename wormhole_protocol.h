#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <openssl/md5.h>

#define	DEFAULT_PORT	60000

#define	SALT_LENGTH	8

enum {
	CODE_DATA=0,
	CODE_KEY_SYNC,
	CODE_CONNECT,
	CODE_CONF_IPV4,
	CODE_PING,
	CODE_PONG,
};

#define	CONNID_PLAIN	0x0000000000000000ULL
#define	CONNID_INVAL	0xffffffffffffffffULL

struct frame_body_st {
	uint8_t code;
	uint32_t fecg_id:24;
	uint32_t fec_seq:8;
	uint8_t fec_config;
	union {
		struct {
			uint8_t recver_tun_addr[16];
			uint8_t sender_tun_addr[16];
		} conf_ipv4;
		struct {
			uint64_t conn_id;
		} key_accept;
		struct {
			uint64_t ping_timestamp_ms;
			uint64_t pong_timestamp_ms;
		} echo;
		struct {
			uint8_t data[0];
		} data;
	};
};

struct frame_st {
	uint64_t conn_id;
	union {
		struct {
			uint8_t code;
			uint8_t salt[SALT_LENGTH];
			uint8_t md5[MD5_DIGEST_LENGTH];
			uint8_t client_id[1];
		} key_sync_body;
		struct {
			uint8_t code;
		} key_reject;
		uint8_t crypted_body[0];
	};
}__attribute__((packed));

#endif

