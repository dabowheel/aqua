CFLAGS = -O3 -Wall -pedantic -ansi -s

#all
all: linecount run_examples

# examples
run_examples: examples/string.o
	gcc -o run_examples string.o aqua.o

# linecount
linecount: linecount.o aqua.o
	gcc -o linecount linecount.o aqua.o

linecount.o: examples/linecount.c
	gcc -c examples/linecount.c $(CFLAGS)

# c files
%.o: %.c
	gcc -c $< $(CFLAGS)

# clean
clean:
	rm -f linecount linecount.o aqua.o run_examples
