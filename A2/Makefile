CC = g++
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -I./include/ -I/usr/X11/include -DOSX
	LDFLAGS = -framework GLUT -framework OpenGL \
    	-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
    	-lGL -lGLU -lm -lstdc++
else
	LDFLAGS = -lpng
endif
	
RM = /bin/rm -f 
all: main 
main: Color.o Point.o Vertex.o Material.o Ray.o Vector3.o Image.o PointLight.o DirectedLight.o Triangle.o Polygon.o ray_tracer.o 
	$(CC) $(CFLAGS) -o as1 Color.o Point.o Vertex.o Material.o Ray.o Image.o Vector3.o PointLight.o DirectedLight.o Triangle.o Polygon.o ray_tracer.o $(LDFLAGS)
Image.o: Image.cpp
	$(CC) $(CFLAGS) -c Image.cpp -o Image.o
Color.o: Color.cpp
	$(CC) $(CFLAGS) -c Color.cpp -o Color.o
Vertex.o: Vertex.cpp
	$(CC) $(CFLAGS) -c Vertex.cpp -o Vertex.o
Vector3.o: Vector3.cpp
	$(CC) $(CFLAGS) -c Vector3.cpp -o Vector3.o
Point.o: Point.cpp
	$(CC) $(CFLAGS) -c Point.cpp -o Point.o
Ray.o: Ray.cpp
	$(CC) $(CFLAGS) -c Ray.cpp -o Ray.o
Material.o: Material.cpp
	$(CC) $(CFLAGS) -c Material.cpp -o Material.o
Triangle.o: Triangle.cpp Shape.h Triangle.h
	$(CC) $(CFLAGS) -c Triangle.cpp -o Triangle.o
Polygon.o: Polygon.cpp
	$(CC) $(CFLAGS) -c Polygon.cpp -o Polygon.o
PointLight.o: PointLight.cpp Light.h PointLight.h
	$(CC) $(CFLAGS) -c PointLight.cpp -o PointLight.o
DirectedLight.o: DirectedLight.cpp
	$(CC) $(CFLAGS) -c DirectedLight.cpp -o DirectedLight.o
ray_tracer.o: ray_tracer.cpp
	$(CC) -std=c++11 $(CFLAGS) -c ray_tracer.cpp -o ray_tracer.o
clean: 
	$(RM) *.o as1
 


