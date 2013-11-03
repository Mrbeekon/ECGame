# Makefile

MAKE_INC=${CURDIR}/tools/make
include ${MAKE_INC}/vars.mk

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
