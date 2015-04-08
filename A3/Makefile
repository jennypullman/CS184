CC = g++
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -I./include/ -I/usr/X11/include -DOSX
	LDFLAGS = -framework GLUT -framework OpenGL \
    	-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
    	-lGL -lGLU -lm -lstdc++
else
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -std=c++11
	LDFLAGS = -lglut -lGLU -lGL
endif
	
RM = /bin/rm -f 
all: main 
main: Point.o Curve.o Surface.o example_03.o 
	$(CC) $(CFLAGS) -o as1 Point.o Curve.o Surface.o example_03.o $(LDFLAGS)
Point.o: Point.cpp
	$(CC) $(CFLAGS) -c Point.cpp -o Point.o
Curve.o: Curve.cpp
	$(CC) $(CFLAGS) -c Curve.cpp -o Curve.o
Surface.o: Surface.cpp
	$(CC) $(CFLAGS) -c Surface.cpp -o Surface.o
example_03.o: example_03.cpp
	$(CC) $(CFLAGS) -c example_03.cpp -o example_03.o
clean: 
	$(RM) *.o as1
 


