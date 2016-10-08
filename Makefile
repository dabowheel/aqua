CFLAGS = -O3 -Wall -pedantic -ansi -s
INCLUDES =

all: linecount hw

# linecount
linecount: linecount.o in.o mem.o
	gcc -o linecount linecount.o in.o mem.o
# hw
hw: hw.o mem.o
	gcc -o hw hw.o mem.o
# c files
%.o: %.c
	gcc -c $< $(CFLAGS) $(INCLUDES)
# clean
clean:
	rm -f linecount linecount.o in.o mem.o hw hw.o
