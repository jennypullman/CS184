#include "Triangle.h"

class Polygon: Shape{
public:
	Polygon();
	Polygon(Material mat, Vertex *vertices, int verticesLength, Triangle *triangles, int trianglesLength);

	//instance methods
	Material getMaterial();
	float hit(Ray ray);

private:
	Material material;
	Vertex *vertices;
	Triangle *triangles;
	int verticesLength;
	int trianglesLength;
};