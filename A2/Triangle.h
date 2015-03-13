#include "Shape.h"

class Triangle : Shape{
public:
	Triangle();
	Triangle(Material mat, Vertex vert1, Vertex vert2, Vertex vert3);
	Triangle(Material mat, Vertex vert1, Vertex vert2, Vertex vert3, Vector3 norm1, Vector3 norm2, Vector3 norm3);

	//instance methods
	Material getMaterial();
	float hit(Ray ray);
	void print();

private:
	Material material;
	Vertex vert1, vert2, vert3;
	Vector3 norm1, norm2, norm3;
};