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
win: wc.exe string.exe
wc.exe: wc.obj
	link -out:wc.exe wc.obj ../aqua.obj
wc.obj:
	cl -c wc.c
string.exe: string.obj
	link -out:string.exe string.obj ../aqua.obj
string.obj: string.c
	cl -c string.c
winclean:
	del wc wc.obj
