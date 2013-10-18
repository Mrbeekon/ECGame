# Makefile

# Get OS
UNAME := $(shell uname)

# All source files to be compiled.
SRC := src/*.cpp
# Includes directory
INCLUDE := include/
# Libraries directory
LIB := lib/

# C++ compiler and basic flags
CXX := g++
CXX_FLAGS := -I ${INCLUDE} -L ${LIB}

# Add SDL to compilers flags
CXX_FLAGS += -lSDLmain -lSDL
CXX_FLAGS += -I vendor/SDL/${UNAME}/include


# if windows:
ifeq ($(UNAME),windows32)
	# Add MinGW Library
	CXX_FLAGS += -lmingw32

	# Statically Link
	CXX_FLAGS += -static-libstdc++
	CXX_FLAGS += -static-libgcc

	# Target needs .exe extension
	TARGET := ECGame.exe
else # Linux/etc
	# No extension needed.
	TARGET := ECGame
endif

all: build run

# For VS support
rebuild: build

build: fix clean ${TARGET}


clean:
	rm -fr bin

fix:
	mkdir bin
	-cp lib/${UNAME}/* bin/


${TARGET}:
	${CXX} ${SRC} -o bin/${TARGET} ${CXX_FLAGS}


run:
	bin/${TARGET}
