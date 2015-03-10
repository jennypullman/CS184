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
main: Vector3.o Color.o Image.o Light.o ray_tracer.o 
	$(CC) $(CFLAGS) -o as1 Vector3.o Light.o Color.o Image.o ray_tracer.o $(LDFLAGS)
Vector3.o: Vector3.cpp
	$(CC) $(CFLAGS) -c Vector3.cpp -o Vector3.o
Color.o: Color.cpp
	$(CC) $(CFLAGS) -c Color.cpp -o Color.o
Image.o: Image.cpp
	$(CC) $(CFLAGS) -c Image.cpp -o Image.o
Light.o: Light.cpp
	$(CC) $(CFLAGS) -c Light.cpp -o Light.o
ray_tracer.o: ray_tracer.cpp
	$(CC) $(CFLAGS) -c ray_tracer.cpp -o ray_tracer.o
clean: 
	$(RM) *.o as1
 


