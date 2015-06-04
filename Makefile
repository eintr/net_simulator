PREFIX=/usr/local
SBINDIR=$(PREFIX)/sbin

#######################################
all:
%:
	make -C lib $@
	make -C server $@
	make -C client $@

install: all
	[ -d $(PREFIX) ] || mkdir -p $(PREFIX)
	[ -d $(SBINDIR) ] || mkdir $(SBINDIR)
	[ -d $(CONFDIR) ] || mkdir $(CONFDIR)
	make -C src $@

