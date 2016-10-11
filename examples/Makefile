CFLAGS = -O3 -Wall -pedantic -s
version = 1.0.1
LDFLAGS = -L..
LDLIBS = -laqua

# UNIX
all: wc string
wc: wc.o
	gcc -o wc wc.o $(LDFLAGS) $(LDLIBS)
string: string.o
	gcc -o string string.o $(LDFLAGS) $(LDLIBS)
%.o: %.c
	gcc -c $< $(CFLAGS)
clean:
	rm wc string *.o

# Windows
win: wc.exe
wc.exe: wc.c
	msbuild MyProgram.vcxproj /p:Configuration=Debug /p:Platform=X86
winclean:
	rmdir /s /q Debug
