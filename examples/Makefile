CFLAGS = -O3 -Wall -pedantic -s

# all
all: wc string

# wc
wc: wc.o
	gcc -o wc wc.o ../aqua.o

# string
string: string.o
	gcc -o string string.o ../aqua.o

# c files
%.o: %.c
	gcc -c $< $(CFLAGS)

# clean
clean:
	rm wc string *.o
