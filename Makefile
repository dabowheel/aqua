CFLAGS = -O3 -Wall -pedantic -ansi -s
INCLUDES =

#all
all: linecount hw run_examples

# examples
run_examples: examples/string.o
	gcc -o run_examples string.o base.o

# linecount
linecount: linecount.o base.o
	gcc -o linecount linecount.o base.o

# hw
hw: hw.o base.o
	gcc -o hw hw.o base.o

# c files
%.o: %.c
	gcc -c $< $(CFLAGS) $(INCLUDES)

# clean
clean:
	rm -f linecount linecount.o hw hw.o base.o run_examples
