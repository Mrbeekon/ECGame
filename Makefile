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

	# Windows NULL
	NULL := NUL

	# Color definitions. 
	NO_COLOR := 
	OK_COLOR := 
	ERROR_COLOR := 
	WARN_COLOR := 

	OK_STRING := 
	ERROR_STRING := 
	WARN_STRING := 

	# Echoes
	ECHO := echo
	ECHO_N := ${ECHO}
	ECHO_E := ${ECHO}

	# Windows specific fix command.
	# Dlls are needed to be copied
	# into bin.
	FIX := cp lib/${UNAME}/*.dll bin/

else # Linux/etc
	# No extension needed.
	TARGET := ECGame

	# Linux NULL
	NULL := /dev/null

	# Color definitions. 
	NO_COLOR := \x1b[0m
	OK_COLOR := \x1b[32;01m
	ERROR_COLOR := \x1b[31;01m
	WARN_COLOR := \x1b[33;01m

	OK_STRING := "$(OK_COLOR)[OK]$(NO_COLOR)"
	ERROR_STRING := "$(ERROR_COLOR)[ERRORS]$(NO_COLOR)"
	WARN_STRING := "$(WARN_COLOR)[WARNINGS]$(NO_COLOR)"

	# Echoes
	ECHO := echo
	ECHO_N := ${ECHO} -n
	ECHO_E := ${ECHO} -e

	# Linux specific fix command.
	# Actually nothing needed so
	# just echoes into null.
	FIX := ${ECHO} > ${NULL}
endif

# Add SDL to compilers flags
CXX_FLAGS += -lSDLmain -lSDL
CXX_FLAGS += -I vendor/SDL/${UNAME}/include


all: build run

# For VS support
rebuild: build

build: clean fix ${TARGET}


clean:
	@${ECHO_N} "Cleaning... "
	@rm -fr bin
	@${ECHO_E} ${OK_STRING}


fix:
	@${ECHO_N} "Fixing... "
	@mkdir bin
	@${FIX}
	@${ECHO_E} ${OK_STRING}


${TARGET}:
	@${ECHO_N} "Building ${TARGET}... "
	@${CXX} ${SRC} -o bin/${TARGET} ${CXX_FLAGS}
	@${ECHO_E} ${OK_STRING}


run:
	@${ECHO} "Running ${TARGET}... "
	@bin/${TARGET}
	@${ECHO_E} ${OK_STRING}
