# Makefile

# Get OS
UNAME := $(shell uname)

CXX := g++
CXX_FLAGS := -I include/ -L lib/ -lSDLmain -lSDL
CXX_FLAGS += -I vendor/SDL/${UNAME}/include
SRC := src/*.cpp

ifeq ($(UNAME),windows32)
	CXX_FLAGS += -lmingw32 -lSDLmain -static-libstdc++ -static-libgcc
	TARGET := ECGame.exe
else
	TARGET := ECGame
endif

all: build run

rebuild: all
	
clean:
	rm -fr bin include/SDL

fix:
	mkdir bin
	-cp lib/${UNAME}/* bin/

SDL:
	cp -r vendor/SDL/${UNAME} include/SDL

${TARGET}:
	${CXX} ${SRC} -o bin/${TARGET} ${CXX_FLAGS}


build: ${TARGET}

run:
	bin/${TARGET}
