include_dirs = -I../..
CFLAGS = -O3 -Wall -pedantic -s $(include_dirs)
version = 1.0.1
LDFLAGS = -L../..
LDLIBS = -laqua

# UNIX
string: string.o
	gcc -o string string.o $(LDFLAGS) $(LDLIBS)
%.o: %.c
	gcc -c $< $(CFLAGS)
clean:
	rm -f string *.o
