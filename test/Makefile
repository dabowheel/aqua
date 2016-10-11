include_dirs = -I../external/Criterion/include -I..
CFLAGS = -O3 -Wall -pedantic -s $(include_dirs)
LDFLAGS = -L../external/Criterion/build -L..
LDLIBS = -lcriterion -laqua

# UNIX
all: get main
main: main.o
	gcc -o main main.o $(LDLIBS) $(LDFLAGS)
aqua.o: aqua.c
	gcc -c aqua.c $(CFLAGS)
get:
	if [ ! -d ../external/Criterion ]; then git clone git@github.com:Snaipe/Criterion.git ../external/Criterion; fi
	if [ ! -d ../external/Criterion/build ]; then cd ../external/Criterion; mkdir build; cd build; cmake ..; cmake --build .; fi
clean:
	rm -f main main.o
	rm -rf ../external/Criterion
run:
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../external/Criterion/build:.. ./main

# WINDOWS
win: winget main.exe
winget:
	if not exist ../external/Criterion git clone git@github.com:Snaipe/Criterion.git ../external/Criterion
	if not exist ../external/Criterion/build cd ../external/Criterion && mkdir build && cd build && cmake .. && cmake --build .
main.exe: main.c
	msbuild /p:Configuration=Debug /p:Platform=X86
	copy Debug\AquaTest.exe main.exe
	copy ..\external\Criterion\build\Debug\criterion.dll criterion.dll
winclean:
	del *.obj *.exe *.dll
	rmdir /S /Q Debug
