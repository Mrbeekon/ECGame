# Makefile

SHELL := /bin/bash

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

# Add SDL to compilers flags
CXX_FLAGS += -lSDLmain -lSDL
CXX_FLAGS += -I vendor/SDL/${UNAME}/include


# Color definitions. 
NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m
ERROR_COLOR=\x1b[31;01m
WARN_COLOR=\x1b[33;01m

OK_STRING="$(OK_COLOR)[OK]$(NO_COLOR)"
ERROR_STRING="$(ERROR_COLOR)[ERRORS]$(NO_COLOR)"
WARN_STRING="$(WARN_COLOR)[WARNINGS]$(NO_COLOR)"

all: build run

# For VS support
rebuild: build

build: clean fix ${TARGET}


clean:
	@echo -n "Cleaning ... "
	@rm -fr bin
	@echo -e ${OK_STRING}


fix:
	@echo -n "Fixing ... "
	@mkdir bin
	@-cp lib/${UNAME}/* bin/  > /dev/null 2>&1 | true  && true
	@echo -e ${OK_STRING}


${TARGET}:
	@echo -n "Building ${TARGET} ... "
	@${CXX} ${SRC} -o bin/${TARGET} ${CXX_FLAGS}
	@echo -e ${OK_STRING}


run:
	@echo "Running ${TARGET} ... "
	@bin/${TARGET}
	@echo -e ${OK_STRING}
