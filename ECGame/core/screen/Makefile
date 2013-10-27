# Name of the file(s) we're compiling

TARGET = screen

# location of the Python header files

PYTHON = /usr/include/python2.7

# location of the Boost Python include files and library

BOOST_INC = /usr/include
BOOST_LIB = /usr/lib

SDL_LIB = -lSDLmain -lSDL
SDL_INC = -I ../../c/vendor/SDL/linux/include

$(TARGET).so: $(TARGET).o
	g++ -shared -Wl,--export-dynamic \
	${TARGET}.o -L$(BOOST_LIB) -lboost_python \
	-L/usr/lib/python2.1/config -lpython2.7 \
	${SDL_LIB} -o ../${TARGET}.so
 
$(TARGET).o: clean
	g++ -I$(PYTHON) -I$(BOOST_INC) ${SDL_INC} -c $(TARGET).cpp -fPIC

clean:
	rm -f *.o *.dll *.a *~ ../${TARGET}.so
