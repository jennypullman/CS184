CC = g++
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -I./include/ -I/usr/X11/include -DOSX
	LDFLAGS = -framework GLUT -framework OpenGL \
    	-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
    	-lGL -lGLU -lm -lstdc++
else
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -Iglut-3.7.6-bin
	LDFLAGS = -lglut -lGLU -lGL
endif
	
RM = /bin/rm -f 
all: main 
main: Vector3.o Color.o Image.o example_01.o 
	$(CC) $(CFLAGS) -o as1 Vector3.o Color.o Image.o example_01.o $(LDFLAGS)
Vector3.o: Vector3.cpp
	$(CC) $(CFLAGS) -c Vector3.cpp -o Vector3.o
Color.o: Color.cpp
	$(CC) $(CFLAGS) -c Color.cpp -o Color.o
Image.o: Image.cpp
	$(CC) $(CFLAGS) -c Image.cpp -o Image.o
example_01.o: example_01.cpp
	$(CC) $(CFLAGS) -c example_01.cpp -o example_01.o
clean: 
	$(RM) *.o as1
 


