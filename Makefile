SOURCEDIR = "external"
BSTRDIR = $(SOURCEDIR)/bstrlib
CFLAGS = -O3 -Wall -pedantic -ansi -s

all: get linecount hw

# linecount
linecount: linecount.o in.o mem.o
	gcc -o linecount linecount.o in.o mem.o
linecount.o: linecount.c
	gcc -c linecount.c $(CFLAGS)

# base
in.o: in.c
	gcc -c in.c $(CFLAGS)
mem.o: mem.c
	gcc -c mem.c $(CFLAGS)

# hw
hw: hw.o bstrlib.o
	gcc -o hw hw.o bstrlib.o

hw.o: hw.c
	gcc -c hw.c $(CFLAGS)

bstrlib.o:
	gcc -c $(BSTRDIR)/bstrlib.c $(CFLAGS)

get:
	git clone git@github.com:websnarf/bstrlib.git external/bstrlib

# utilities
clean:
	rm -f linecount linecount.o in.o mem.o hw hw.o bstrlib.o
	rm -rf external