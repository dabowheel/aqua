include_dirs = -I../external/Criterion/include
CFLAGS = -O3 -Wall -pedantic -s $(include_dirs)
LDFLAGS = -L../external/Criterion/build
LDLIBS = -lcriterion
CL = "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\cl"
LINK = "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\link"

# UNIX
all: get aqua
aqua: aqua.o
	gcc -o aqua aqua.o ../aqua.o $(LDLIBS) $(LDFLAGS)
aqua.o: aqua.c
	gcc -c aqua.c $(CFLAGS)
get:
	if [ ! -d ../external/Criterion ]; then git clone git@github.com:Snaipe/Criterion.git ../external/Criterion; fi
	if [ ! -d ../external/Criterion/build ]; then cd ../external/Criterion; mkdir build; cd build; cmake ..; cmake --build .; fi
clean:
	rm -f aqua.o aqua
	rm -rf ../external/Criterion
run:
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../external/Criterion/build ./aqua

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
