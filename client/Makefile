PREFIX=/usr/local
SBINDIR=$(PREFIX)/sbin

#######################################

CFLAGS+=-I../include/ -pthread -Wall -g -D_GNU_SOURCE -O0

LDFLAGS+=-lpthread -lm -lssl -lcrypto -lrt -L../ -lwormhole_util

TARGETS=wormhole_client

sources=client.c  client_conn.c  main.c

objects=$(sources:.c=.o)

all: $(TARGETS)

wormhole_client: $(objects)
	    $(CC) -o $@ $^ $(LDFLAGS)

install: all
	    $(INSTALL) $(TARGETS) $(SBINDIR)/

clean:
	    rm -f $(objects) $(TARGETS)

