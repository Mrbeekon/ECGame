# Makefile

clean:
	rm -fr bin
	rm -fr obj

fix:
	mkdir bin
	mkdir obj
	cp lib/SDL.dll bin/ -r

build:
	g++ src/ECGame.cpp -o bin/ECGame.exe -I include/ -L lib/ -lmingw32 -lSDLmain -lSDL -static-libstdc++
	
rebuild: clean fix build
	
all: rebuild
