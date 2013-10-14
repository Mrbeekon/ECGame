# Makefile
UNAME := $(shell uname)

# All should be first rule.
all: rebuild

clean:
	rm -fr bin
	rm -fr obj

fix:
	mkdir bin
	mkdir obj
	cp lib/*.dll bin/

# Windows builds
ECGame.exe:
	g++ src/*.cpp -o bin/ECGame.exe -I include/ -L lib/ -lmingw32 -lSDLmain -lSDL -static-libstdc++ -static-libgcc -static-libg++
rebuild-win: clean fix ECGame.exe
all-win: rebuild-win

# All other builds. For Linux, OSX, Unix and any other POSIX OS.
ECGame:
	g++ src/*.cpp -o bin/ECGame -I include/ -L lib/ -lSDLmain -lSDL
rebuild: clean fix ECGame

