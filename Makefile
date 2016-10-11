CFLAGS = -O3 -Wall -pedantic -s
CC = gcc
majorversion = 1
version = $(majorversion).0.1
installpath = /usr/local

# UNIX
all: libaqua.so
aqua.o: aqua.c
	$(CC) -c -fPIC aqua.c $(CFLAGS)
libaqua.so.$(version): aqua.o
	$(CC) -shared -Wl,-soname,libaqua.so.1 -o libaqua.so.$(version) aqua.o
clean:
	rm -f aqua.o aqua.so.*
install:
	cp libaqua.so.$(version) $(installpath)/lib
	cd $(installpath)/lib; ln -s libaqua.so.$(version) libaqua.so.$(majorversion)
	cp aqua.h $(installpath)/include
uninstall:
	rm -f $(installpath)/lib/libaqua.so.1
	rm -f $(installpath)/lib/libaqua.so.$(version)
	rm -f $(installpath)/include/aqua.h

# Windows
win: aqua.obj
aqua.obj:
	cl -c aqua.c
winclean:
	del aqua.obj
