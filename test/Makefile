include_dirs = -I../external/Criterion/include -I../include
CFLAGS = -O3 -Wall -pedantic -s -g $(include_dirs)
LDFLAGS = -L../external/Criterion/build -L../build
LDLIBS = -lcriterion -laqua

# UNIX
all: get main
main: main.o
	gcc -o main main.o $(LDLIBS) $(LDFLAGS)
%.o: %.c
	gcc -c $< $(CFLAGS)
get:
	if [ ! -d ../external/Criterion ]; then git clone git@github.com:Snaipe/Criterion.git ../external/Criterion; fi
	if [ ! -d ../external/Criterion/build ]; then cd ../external/Criterion; mkdir build; cd build; cmake ..; cmake --build .; fi
clean:
	rm -f main main.o
	rm -rf ../external/Criterion
run:
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../external/Criterion/build:../build ./main
