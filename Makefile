CFLAGS = -O3 -Wall -pedantic -s
CC = gcc

# UNIX
all: aqua.o
aqua.o: aqua.c
	$(CC) -c aqua.c $(CFLAGS)
clean:
	rm -f aqua.o

# Windows
win: aqua.dll
aqua.dll:
	msbuild LibAqua.sln /p:Configuration=Debug /p:Platform=X86
winclean:
	rmdir /s /q Debug || rmdir /s /q examples\Debug
