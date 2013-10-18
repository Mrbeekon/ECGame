# Makefile

# Get OS
UNAME := $(shell uname)

all: rebuild run

### LINUX ###

clean:
	rm -fr bin obj include/SDL

fix:
	mkdir bin
	mkdir obj
	-cp lib/${UNAME}/* bin/

SDL:
	cp -r vendor/SDL/${UNAME} include/SDL

### LINUX ###

ECGamr:
	g++ src/*.cpp -o bin/ECGame -I include/ -L lib/ -lSDLmain -lSDL

rebuild: clean fix ECGame

build: ECGame

run:
	bin/ECGame

### WINDOWS ###

wECGame:
	g++ src/*.cpp -o bin/ECGame.exe -I include/ -I vendor/SDL/windows32/include/ -L lib/ -lmingw32 -lSDLmain -lSDL -static-libstdc++ -static-libgcc

wrebuild: clean fix wECGame

wbuild: wECGame

wrun:
	bin/ECGame.exe