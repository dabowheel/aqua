cflags = -g
linecount: linecount.o in.o mem.o
	gcc -o linecount linecount.o in.o mem.o
linecount.o: linecount.c
	gcc -c linecount.c $(cflags)
in.o: in.c
	gcc -c in.c $(cflags)
mem.o: mem.c
	gcc -c mem.c $(cflags)
clean:
	rm -f linecount linecount.o in.o mem.o