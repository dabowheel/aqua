CC = gcc
link_version = 0.1
release_version = $(link_version).1
installpath = /usr/local
includepath = -I../include
CFLAGS = -Wall -pedantic -s $(includepath) -g

# UNIX
all: build build/libaqua.so
build:
	mkdir -p build
build/libaqua.so: build/urlcode.o build/string_builder.o build/util.o build/string.o build/hash_table.o build/form.o
	cd build; $(CC) -shared -Wl,-soname,libaqua.so.$(link_version) -o libaqua.so.$(link_version) urlcode.o string_builder.o util.o string.o hash_table.o form.o
	cd build; ln -s -f libaqua.so.$(link_version) libaqua.so
build/%.o: src/%.c
	cd build; $(CC) -c -fPIC ../$< $(CFLAGS)

clean:
	rm -rf build

install:
	cp build/libaqua.so $(installpath)/lib/libaqua.so.$(link_version)
	cd $(installpath)/lib; ln -s -f libaqua.so.$(link_version) libaqua.so
	cp -r include/aqua $(installpath)/include
uninstall:
	rm -f $(installpath)/lib/libaqua.so
	rm -f $(installpath)/lib/libaqua.so.$(link_version)
	rm -rf $(installpath)/include/aqua

# Windows
win:
	set ExternalCompilerOptions=/DWINAPI
	msbuild aqua.sln /p:Configuration=Debug /p:Platform=X86
	copy external\Criterion\build\Debug\criterion.dll Debug
winclean:
	if exist Debug rmdir /s /q Debug
	if exist examples\string\Debug rmdir /s /q examples\string\Debug
	if exist examples\wc\Debug rmdir /s /q examples\wc\Debug
	if exist test\Debug rmdir /s /q test\Debug
	