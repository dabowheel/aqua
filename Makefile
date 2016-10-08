CFLAGS = -O3 -Wall -pedantic -ansi -s
INCLUDES =

#all
all: linecount hw run_examples

# examples
run_examples: examples/string.o
	gcc -o run_examples string.o aqua.o

# linecount
linecount: linecount.o aqua.o
	gcc -o linecount linecount.o aqua.o

# hw
hw: hw.o aqua.o
	gcc -o hw hw.o aqua.o

# c files
%.o: %.c
	gcc -c $< $(CFLAGS) $(INCLUDES)

# clean
clean:
	rm -f linecount linecount.o hw hw.o aqua.o run_examples
