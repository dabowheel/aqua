CFLAGS = -O3 -Wall -pedantic -s

# UNIX
all: wc string
wc: wc.o
	gcc -o wc wc.o ../aqua.o
string: string.o
	gcc -o string string.o ../aqua.o
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
