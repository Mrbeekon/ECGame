# Makefile

# Name of output binary.
TARGET := ECGame

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
CXX_INCS := -I ${INCLUDE}
CXX_LIBS := -L ${LIB}

# C++ Standard
CXX_FLAGS := -std=c++11

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

SHARED_OBJ := ${TARGET}.so

# if windows:
ifeq ($(UNAME),windows32)
	# Add MinGW Library
	CXX_LIBS += -lmingw32

	# Statically link
	CXX_FLAGS += -static-libstdc++
	CXX_FLAGS += -static-libgcc

	# Output has dll extension
	SHARED_OBJ := ${TARGET}.dll

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
	CLEAN_STRING := Cleaning...
	FIX_STRING := Fixing...
	BUILD_STRING := Building ${TARGET}...
	RUN_STRING := Running ${TARGET}...

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
CXX_LIBS += -lSDLmain -lSDL
CXX_INCS += -I vendor/SDL/${UNAME}/include

CXX_INCS += -I /usr/include/python2.7
CXX_LIBS += -L /usr/lib/python2.1/config -lpython2.7

CXX_INCS += -I /usr/include
CXX_LIBS += -L /usr/lib -lboost_python



all: build

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
	@${CXX} ${CXX_INCS} ${CXX_FLAGS}  -c src/${TARGET}.cpp -o ${TARGET}.o -fPIC

	@${CXX} -shared -Wl,--export-dynamic ${TARGET}.o ${CXX_LIBS} -o ${SHARED_OBJ}
	@${ECHO_E} ${OK_STRING}


run:
	@${ECHO} ${RUN_STRING}
	@bin/${TARGET}
	@${ECHO_E} ${OK_STRING}
