# Makefile

# Get OS
UNAME := $(shell uname)

all: rebuild run

### ENVIRONMENT MANAGEMENT ###

clean:
	rm -fr bin obj include/SDL

fix:
	mkdir bin
	mkdir obj
	ln -s vendor/SDL/${UNAME} include/SDL
	-cp lib/${UNAME}/* bin/


ECGame:
	g++ src/*.cpp -o bin/ECGame -I include/ -L lib/ -lSDLmain -lSDL

rebuild: clean fix ECGame

build: ECGame

run:
	bin/ECGame

### WINDOWS ###
ECGame.exe:
	g++ src/*.cpp -o bin/ECGame.exe -I include/  -L lib/ -lmingw32 -lSDLmain -lSDL -static-libstdc++ -static-libgcc

wrebuild: clean fix ECGame.exe

wbuild: ECGame.exe

wrun:
	bin/ECGame.exe
