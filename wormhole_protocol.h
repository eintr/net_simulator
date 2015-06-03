#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <openssl/md5.h>

#define	DEFAULT_PORT	60000

#define	SALT_LENGTH	8

enum {
	CODE_DATA=0,
	CODE_CHAP,
	CODE_CHAP_CONNECT,
	CODE_CHAP_REJECT,
	CODE_CONF_IPV4,
	CODE_PING,
	CODE_PONG,
};

#define	CONNID_PLAIN	0x0000000000000000ULL
#define	CONNID_INVAL	0xffffffffffffffffULL

struct fec_info_st {
	uint32_t fecg_id:24;
	uint32_t fec_seq:8;
	uint8_t fec_config;
};

struct crypted_body_st {
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
	};
};

struct frame_st {
	uint64_t conn_id;
	union {
		struct {
			uint8_t code;
			struct fec_info_st fec_info;
			union {
				struct {
					uint8_t salt[SALT_LENGTH];
					uint8_t md5[MD5_DIGEST_LENGTH];
					uint8_t client_id[1];
				} chap;
				struct {
					uint8_t reason[1];
				} chap_reject;
			};
		} plain_body;
		uint8_t crypted_body[0];	// decrypt to struct crypted_body_st 
	};
}__attribute__((packed));

#endif

