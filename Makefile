CFLAGS = -O3 -Wall -pedantic -s

#all
all: aqua.o

# c files
%.o: %.c
	gcc -c $< $(CFLAGS)

# clean
clean:
	rm -f aqua.o
