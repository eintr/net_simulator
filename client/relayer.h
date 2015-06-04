#ifndef RELAYER_H
#define RELAYER_H

#include "cJSON.h"

void *relay_send_run(struct client_conn_st *c);
void *relay_recv_run(struct client_conn_st *c);

#endif

