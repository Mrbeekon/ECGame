# Makefile

all: clean fix

clean:
	rm -fr bin

fix:
	mkdir bin

demo:
	g++ src/demo.cpp -o bin/demo -lSDL


