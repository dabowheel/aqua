SOURCEDIR = external
BSTRDIR = $(SOURCEDIR)/bstrlib
CFLAGS = -O3 -Wall -pedantic -ansi -s

all: linecount hw

# linecount
linecount: linecount.o in.o mem.o
	gcc -o linecount linecount.o in.o mem.o
# hw
hw: bstrlib.o hw.o
	gcc -o hw hw.o bstrlib.o

# bstring
bstrlib.o:
	git clone git@github.com:websnarf/bstrlib.git external/bstrlib
	gcc -c $(BSTRDIR)/bstrlib.c $(CFLAGS)

%.o: %.c
	gcc -c $< $(CFLAGS)

# utilities
clean:
	rm -f linecount linecount.o in.o mem.o hw hw.o bstrlib.o
	rm -rf external