#ifndef WORMHOLE_MSG_H
#define WORMHOLE_MSG_H

#include "wormhole_protocol.h"

struct internal_frame_st {
};

int msg_decode(char *data, size_t datalen, struct internal_frame_st *dst);
int msg_encode(struct internal_frame_st *src, char *data, size_t *datalen);

#endif

