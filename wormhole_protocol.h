#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <openssl/md5.h>

#define	DEFAULT_PORT	60000

#define	FRAMESIZE_MAX	64000

#define	SALT_LENGTH	8

enum {
	CODE_DATA=0,
	CODE_CHAP,
	CODE_CHAP_CONNECT,
	CODE_CHAP_REJECT,
	CODE_PING,
	CODE_PONG,
	CODE_CLOSE,
};

#define	CONNID_ANY	0x0000000000000000ULL
#define	CONNID_INVAL	0xffffffffffffffffULL

struct fec_info_st {
	uint32_t fecg_id:24;
	uint32_t fec_seq:8;
	uint8_t fec_config;
}__attribute__((packed));

struct frame_body_chap_st {
	uint8_t salt[SALT_LENGTH];
	uint32_t prefix;
	uint8_t prefix_len;
	uint8_t md5[MD5_DIGEST_LENGTH];
	uint8_t client_id[1];
}__attribute__((packed));

struct frame_body_chap_connect_st {
	uint64_t conn_id;
	uint32_t server_tun_addr;
	uint32_t client_tun_addr;
	uint32_t route_prefixes[0];
}__attribute__((packed));

#define	ERR_UNKNOWN		0x10000001UL
#define	ERR_AUTH_FAILED		0x10000002UL
#define	ERR_ROUTE_CONFLICT	0x10000003UL
#define	ERR_ADDRESS_CONFLICT	0x10000003UL
struct frame_body_chap_reject_st {
	uint32_t errcode;
}__attribute__((packed));

struct frame_body_echo_st {
	uint64_t ping_timestamp_ms;
	uint64_t pong_timestamp_ms;
}__attribute__((packed));

struct frame_body_data_st {
	struct fec_info_st fec_info;
	uint8_t data[0];
}__attribute__((packed));

struct frame_st {
	uint64_t conn_id;
	uint8_t code;
	union {
		struct frame_body_chap_st body_chap;
		struct frame_body_chap_connect_st body_chap_connect;
		struct frame_body_chap_reject_st body_chap_reject;
		struct frame_body_echo_st body_echo;
		struct frame_body_data_st body_data;
	};
}__attribute__((packed));

#endif

