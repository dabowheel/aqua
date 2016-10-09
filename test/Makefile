include_dirs = -I../external/Criterion/include
CFLAGS = -O3 -Wall -pedantic -s $(include_dirs)
LDFLAGS = -L../external/Criterion/build
LDLIBS = -lcriterion

aqua: aqua.o
	gcc -o aqua aqua.o ../aqua.o $(LDLIBS) $(LDFLAGS)

aqua.o: aqua.c
	gcc -c aqua.c $(CFLAGS)

clean:
	rm -f aqua.o aqua