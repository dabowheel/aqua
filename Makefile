CFLAGS = -O3 -Wall -pedantic -s
CC = gcc
majorversion = 1
version = $(majorversion).0.1
installpath = /usr/local

# UNIX
all: libaqua.so
aqua.o: aqua.c
	$(CC) -c -fPIC aqua.c $(CFLAGS)
libaqua.so: aqua.o
	$(CC) -shared -Wl,-soname,libaqua.so.$(version) -o libaqua.so aqua.o
clean:
	rm -f aqua.o libaqua.so*
install:
	cp libaqua.so $(installpath)/lib/libaqua.so.$(version)
	cd $(installpath)/lib; ln -s -f libaqua.so.$(version) libaqua.so
	cp aqua.h $(installpath)/include
uninstall:
	rm -f $(installpath)/lib/libaqua.so.1
	rm -f $(installpath)/lib/libaqua.so.$(version)
	rm -f $(installpath)/include/aqua.h

# Windows
win: aqua.dll
aqua.dll:
	set ExternalCompilerOptions=/DWINAPI
	msbuild LibAqua.sln /p:Configuration=Debug /p:Platform=X86
winclean:
	rmdir /s /q Debug || rmdir /s /q examples\Debug
