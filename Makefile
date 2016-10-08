SOURCEDIR = external
BSTRDIR = $(SOURCEDIR)/bstrlib
CFLAGS = -O3 -Wall -pedantic -ansi -s
INCLUDES = -I$(BSTRDIR)

all: get linecount hw

# linecount
linecount: linecount.o in.o mem.o bstrlib.o
	gcc -o linecount linecount.o in.o mem.o bstrlib.o
# hw
hw: bstrlib.o hw.o mem.o
	gcc -o hw hw.o bstrlib.o mem.o

# bstring
bstrlib.o:
	gcc -c $(BSTRDIR)/bstrlib.c $(CFLAGS)

%.o: %.c
	gcc -c $< $(CFLAGS) $(INCLUDES)

get:
	if [ ! -d external/bstrlib ]; then git clone git@github.com:websnarf/bstrlib.git external/bstrlib; fi

# utilities
clean:
	rm -f linecount linecount.o in.o mem.o hw hw.o bstrlib.o
	rm -rf external
