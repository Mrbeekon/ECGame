# Main vars

SHELL := /bin/bash

# Get OS
UNAME := $(shell uname)

# All source files to be compiled.
SRC :=  ${CURDIR}/src/*.cpp
# Includes directory
INCLUDE :=  ${CURDIR}/include/
# Libraries directory
LIB :=  ${CURDIR}/lib/

# C++ compiler and basic flags
CXX := g++
CXX_FLAGS := -I ${INCLUDE} -L ${LIB}

# Turn on Warnings
CXX_FLAGS += -Wall

# C++ Standard
CXX_FLAGS += -std=c++11

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
# Actually nothing needed to fix for standard OSes.
FIX := ${ECHO} > ${NULL}

-include ${MAKE_INC}/vars.$(UNAME).mk

# Add SDL to compilers flags
CXX_FLAGS += -lSDLmain -lSDL
CXX_FLAGS += -I  ${CURDIR}/vendor/SDL/${UNAME}/include
