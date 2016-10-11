CFLAGS = -O3 -Wall -pedantic -s
version = 1.0.1
LDFLAGS = -L../..
LDLIBS = -laqua

# UNIX
wc: wc.o
	gcc -o wc wc.o $(LDFLAGS) $(LDLIBS)
%.o: %.c
	gcc -c $< $(CFLAGS)
clean:
	rm -f wc *.o
