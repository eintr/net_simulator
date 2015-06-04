#ifndef FEC_H
#define FEC_H

#include <time.h>

struct fec_processor_stat_st {
	time_t timeout;
	uint64_t count;
	uint64_t lost, dup, late;
	uint64_t corrected, failed;
};

typedef void fec_processor_t;

typedef void protocol_process_func(struct internal_frame_st*);

fec_processor_t *fec_processor_new(void);
int fec_processor_delete(fec_processor_t *);

int fec_processor_settimeout(fec_processor_t *, time_t);
int fec_processor_setfalgs(fec_processor_t *, int);
int fec_processor_statics(fec_processor_t *, struct fec_processor_stat_st*);

enum fec_status {
	FEC_OK=0,
	FEC_NEEDMORE,
	FEC_DUP,
	FEC_TOOLATE
};
int fec_frame_recv(fec_processor_t *, struct fec_frame_st*, int size, );

int fec_frame_send(fec_processor_t *, void*, int size, );

#endif

