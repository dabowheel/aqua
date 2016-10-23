CC = gcc
link_version = 0.2
release_version = $(link_version).1
installpath = /usr/local
includepath = -I../include
base_cflags = -Wall -pedantic -s $(includepath)
objects = urlcode.o string_builder.o util.o string.o hash_table.o form.o
debug_flags =

# UNIX
release: sharedlib_target = sharedlib
release: staticlib_target = staticlib
release: libs

debug: sharedlib_target = debug_sharedlib
debug: staticlib_target = debug_staticlib
debug: libs

libs: root_sharedlib root_staticlib

root_sharedlib:
	mkdir -p build/shared
	make -C build/shared -f ../../Makefile $(sharedlib_target)

root_staticlib:
	mkdir -p build/static
	make -C build/static -f ../../Makefile $(staticlib_target)

debug_sharedlib: debug_flags = -g
debug_sharedlib: libaqua.so
sharedlib: libaqua.so
libaqua.so: CFLAGS = $(base_cflags) -fPIC $(debug_flags)
libaqua.so: $(objects)
	$(CC) -shared -Wl,-soname,libaqua.so.$(link_version) -o libaqua.so.$(link_version) $(objects)
	ln -s -f libaqua.so.$(link_version) libaqua.so

debug_staticlib: debug_flags = -g
debug_staticlib: libaqua.a
staticlib: libaqua.a
libaqua.a: CFLAGS = $(base_cflags) $(debug_flags)
libaqua.a: $(objects)
	ar rcs libaqua.a $(objects)

%.o: ../../src/%.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -rf build

install:
	cp build/shared/libaqua.so.$(link_version) $(installpath)/lib
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
	