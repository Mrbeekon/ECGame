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

# Name of output binary.
TARGET := ECGame

# General NULL
NULL := /dev/null

# Colour definitions.
NO_COLOUR := \x1b[0m
OK_COLOUR := \x1b[32;01m
ERROR_COLOUR := \x1b[31;01m
WARN_COLOUR := \x1b[33;01m

# Status messages
OK_STRING := "$(OK_COLOUR)[OK]$(NO_COLOUR)"
ERROR_STRING := "$(ERROR_COLOUR)[ERRORS]$(NO_COLOUR)"
WARN_STRING := "$(WARN_COLOUR)[WARNINGS]$(NO_COLOUR)"

# Task Info Strings
CLEAN_STRING := "Cleaning..."
FIX_STRING := "Fixing..."
BUILD_STRING := "Building ${TARGET}..."
RUN_STRING := "Running ${TARGET}..."

# Echoes
ECHO := echo
ECHO_N := ${ECHO} -n
ECHO_E := ${ECHO} -e

# Fix command.
# Actually nothing needed as
# OS specific.
FIX := ${ECHO} > ${NULL}

ifneq (,$(findstringMINGW32_NT-,$(UNAME)))
    $(UNAME) := windows32

# if windows:
ifeq ($(UNAME),windows32)
	# Add MinGW Library
	CXX_FLAGS += -lmingw32

	# Statically link
	CXX_FLAGS += -static-libstdc++
	CXX_FLAGS += -static-libgcc

	# Target needs .exe extension
	TARGET := ${TARGET}.exe

	# Windows NULL
	NULL := NUL

	# Colour definitions.
	NO_COLOUR :=
	OK_COLOUR :=
	ERROR_COLOUR :=
	WARN_COLOUR :=

	# Status messages
	OK_STRING := [OK]
	ERROR_STRING := [ERRORS]
	WARN_STRING := [WARNINGS]

	# Task Info Strings
	CLEAN_STRING := | SET /P var=Cleaning...
	FIX_STRING := | SET /P var=Fixing...
	BUILD_STRING := | SET /P var=Building ${TARGET}...
	RUN_STRING := | SET /P var=Running ${TARGET}...

	# Echoes
	ECHO := echo
	ECHO_N := ${ECHO}
	ECHO_E := ${ECHO}

	# Windows specific fix command.
	# Dlls are needed to be copied
	# into bin.
	FIX := cp lib/${UNAME}/*.dll bin/

endif

# Add SDL to compilers flags
CXX_FLAGS += -lSDLmain -lSDL
CXX_FLAGS += -I vendor/SDL/${UNAME}/include


all: build run

# For VS support
rebuild: build

build: clean fix ${TARGET}


clean:
	@${ECHO_N} ${CLEAN_STRING}
	@rm -fr bin
	@${ECHO_E} ${OK_STRING}


fix:
	@${ECHO_N} ${FIX_STRING}
	@mkdir bin
	@${FIX}
	@${ECHO_E} ${OK_STRING}


${TARGET}:
	@${ECHO_N} ${BUILD_STRING}
	@${CXX} ${SRC} -o bin/${TARGET} ${CXX_FLAGS}
	@${ECHO_E} ${OK_STRING}


run:
	@${ECHO} ${RUN_STRING}
	@bin/${TARGET}
	@${ECHO_E} ${OK_STRING}
