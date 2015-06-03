#ifndef TUN_H
#define TUN_H

int tun_alloc(char *dev);

int tun_addr(char *dev, char *local, char *peer);

int tun_route(char *dev, char *prefix);

#endif

