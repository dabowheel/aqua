CFLAGS = -O3 -Wall -pedantic -s
CC = gcc

# UNIX
all: aqua.o
aqua.o: aqua.c
	$(CC) -c aqua.c $(CFLAGS)
clean:
	rm -f aqua.o

# Windows
win: aqua.obj
aqua.obj:
	cl -c aqua.c
winclean:
	del aqua.obj
