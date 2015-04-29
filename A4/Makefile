CC = g++
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -I./include/ -I/usr/X11/include -DOSX -I/usr/local/Cellar/libpng/1.6.16/include/libpng16
	LDFLAGS = -framework GLUT -framework OpenGL \
    	-L/usr/local/Cellar/libpng/1.6.16/lib -lpng16 \
    	-lm -lstdc++
else
	LDFLAGS = -lpng
endif
	
RM = /bin/rm -f 
all: main 
main: Color.o Point.o Vertex.o ViewPlane.o Material.o Ray.o Camera.o Vector3.o Transformation.o Image.o Light.o AmbientLight.o PointLight.o DirectedLight.o Shape.o Triangle.o Polygon.o Ellipsoid.o kinematics_solver.o 
	$(CC) $(CFLAGS) -o as1 Color.o Point.o Vertex.o ViewPlane.o Vector3.o Ray.o Camera.o Transformation.o Material.o Image.o Light.o AmbientLight.o PointLight.o DirectedLight.o Shape.o Triangle.o Polygon.o Ellipsoid.o kinematics_solver.o $(LDFLAGS)
Image.o: Image.cpp
	$(CC) $(CFLAGS) -c Image.cpp -o Image.o
Color.o: Color.cpp
	$(CC) $(CFLAGS) -c Color.cpp -o Color.o
Vertex.o: Vertex.cpp
	$(CC) $(CFLAGS) -c Vertex.cpp -o Vertex.o
ViewPlane.o: ViewPlane.cpp
	$(CC) $(CFLAGS) -c ViewPlane.cpp -o ViewPlane.o
Vector3.o: Vector3.cpp
	$(CC) $(CFLAGS) -c Vector3.cpp -o Vector3.o
Transformation.o: Transformation.cpp
	$(CC) -std=c++11 $(CFLAGS) -c Transformation.cpp -o Transformation.o
Point.o: Point.cpp
	$(CC) $(CFLAGS) -c Point.cpp -o Point.o
Ray.o: Ray.cpp
	$(CC) $(CFLAGS) -c Ray.cpp -o Ray.o
Camera.o: Camera.cpp
	$(CC) $(CFLAGS) -c Camera.cpp -o Camera.o
Material.o: Material.cpp
	$(CC) $(CFLAGS) -c Material.cpp -o Material.o
Triangle.o: Triangle.cpp Shape.h Triangle.h
	$(CC) $(CFLAGS) -c Triangle.cpp -o Triangle.o
Polygon.o: Polygon.cpp
	$(CC) $(CFLAGS) -c Polygon.cpp -o Polygon.o
Ellipsoid.o: Ellipsoid.cpp
	$(CC) $(CFLAGS) -c Ellipsoid.cpp -o Ellipsoid.o
Light.o: Light.cpp
	$(CC) $(CFLAGS) -c Light.cpp -o Light.o
AmbientLight.o: AmbientLight.cpp
	$(CC) $(CFLAGS) -c AmbientLight.cpp -o AmbientLight.o
PointLight.o: PointLight.cpp
	$(CC) $(CFLAGS) -c PointLight.cpp -o PointLight.o
DirectedLight.o: DirectedLight.cpp
	$(CC) $(CFLAGS) -c DirectedLight.cpp -o DirectedLight.o
Shape.o: Shape.cpp
	$(CC) $(CFLAGS) -c Shape.cpp -o Shape.o
kinematics_solver.o: kinematics_solver.cpp
	$(CC) -std=c++11 $(CFLAGS) -c kinematics_solver.cpp -o kinematics_solver.o
clean: 
	$(RM) *.o as1
 


