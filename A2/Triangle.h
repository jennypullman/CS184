#include "Shape.h"
#include "Vertex.h"

class Triangle : Shape{
public:
	Triangle();
	Triangle(Material mat, Vertex vert1, Vertex vert2, Vertex vert3);

	//instance methods
	Material getMaterial();
	float hit(Ray ray);

private:
	Material material;
	Vertex vert1, vert2, vert3;
};