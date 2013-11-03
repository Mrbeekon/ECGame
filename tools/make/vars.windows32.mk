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
FIX := cp ${CURDIR}/lib/${UNAME}/*.dll bin/