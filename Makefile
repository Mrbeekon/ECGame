# Makefile
UNAME := $(shell uname)

clean:
	rm -fr bin
	rm -fr obj

fix:
	mkdir bin
	mkdir obj
	cp lib/SDL.dll bin/ -r

# Windows builds
ECGame.exe:
	g++ src/*.cpp -o bin/ECGame.exe -I include/ -L lib/ -lmingw32 -lSDLmain -lSDL -static-libstdc++	
rebuild-win: clean fix ECGame.exe
all-win: rebuild-win

# All other builds. For Linux, OSX, Unix and any other POSIX OS.
ECGame:
	g++ src/*.cpp -o bin/ECGame -I include/ -L lib/ -lSDLmain -lSDL -static-libstdc++
rebuild: clean fix ECGame
all: rebuild

