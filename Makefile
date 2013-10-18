# Makefile
UNAME := $(shell uname)

all: lrebuild lrun

### ENVIRONMENT MANAGEMENT ###

clean:
	rm -fr bin
	rm -fr obj

fix:
	mkdir bin
	mkdir obj
	cp lib/*.dll bin/

### WINDOWS ###

ECGame.exe:
	g++ src/*.cpp -o bin/ECGame.exe -I include/ -I incwin/ -L lib/ -lmingw32 -lSDLmain -lSDL -static-libstdc++ -static-libgcc

wrebuild: clean fix ECGame.exe

wbuild: ECGame.exe

wrun:
	bin/ECGame.exe

### LINUX\NON-WINDOWS ###

ECGame:
	g++ src/*.cpp -o bin/ECGame -I include/ -I inclinux/ -L lib/ -lSDLmain -lSDL

lrebuild: clean fix ECGame

lbuild: ECGame

lrun:
	bin/ECGame
