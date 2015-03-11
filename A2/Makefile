CC = g++
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -I./include/ -I/usr/X11/include -DOSX
	LDFLAGS = -framework GLUT -framework OpenGL \
    	-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
    	-lGL -lGLU -lm -lstdc++
else
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -Iglut-3.7.6-bin -lm -lpng
endif
	
RM = /bin/rm -f 
all: main 
main: Color.o Image.o ray_tracer.o 
	$(CC) $(CFLAGS) -o as1 Color.o Image.o ray_tracer.o $(LDFLAGS)
Image.o: Image.cpp
	$(CC) $(CFLAGS) -c Image.cpp -o Image.o
Color.o: Color.cpp
	$(CC) $(CFLAGS) -c Color.cpp -o Color.o
ray_tracer.o: ray_tracer.cpp
	$(CC) $(CFLAGS) -c ray_tracer.cpp -o ray_tracer.o
clean: 
	$(RM) *.o as1
 


