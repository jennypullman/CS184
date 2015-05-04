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
main: Point.o UVPoint.o Triangle.o Vector3.o Patch.o Curve.o Surface.o example_03.o 
	$(CC) $(CFLAGS) -o as1 Point.o UVPoint.o Triangle.o Vector3.o Patch.o Curve.o Surface.o example_03.o $(LDFLAGS)
Point.o: Point.cpp
	$(CC) $(CFLAGS) -c Point.cpp -o Point.o
UVPoint.o: UVPoint.cpp
	$(CC) $(CFLAGS) -c UVPoint.cpp -o UVPoint.o
Triangle.o: Triangle.cpp
	$(CC) $(CFLAGS) -c Triangle.cpp -o Triangle.o
Patch.o: Vector3.cpp
	$(CC) $(CFLAGS) -c Vector3.cpp -o Vector3.o
Patch.o: Patch.cpp
	$(CC) $(CFLAGS) -c Patch.cpp -o Patch.o
Curve.o: Curve.cpp
	$(CC) $(CFLAGS) -c Curve.cpp -o Curve.o
Surface.o: Surface.cpp
	$(CC) $(CFLAGS) -c Surface.cpp -o Surface.o
example_03.o: example_03.cpp
	$(CC) $(CFLAGS) -c example_03.cpp -o example_03.o
clean: 
	$(RM) *.o as1
