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
win:
	set ExternalCompilerOptions=/DWINAPI
	msbuild aqua.sln /p:Configuration=Debug /p:Platform=X86
winclean:
	if exist Debug rmdir /s /q Debug
	if exist examples\string\Debug rmdir /s /q examples\string\Debug
	if exist examples\wc\Debug rmdir /s /q examples\wc\Debug
