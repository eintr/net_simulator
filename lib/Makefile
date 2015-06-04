CFLAGS+=-I../include/ -pthread -Wall -g -D_GNU_SOURCE -O3

sources=cJSON.c  ds_llist.c json_conf.c  myrand.c  tun.c  util_time.c

objects=$(sources:.c=.o)

all: libwormhole_util.a

libwormhole_util.a: $(objects)
	ar -cr $@ $^
	ranlib $@

clean:
	    rm -f $(objects) libwormhole_util.a


