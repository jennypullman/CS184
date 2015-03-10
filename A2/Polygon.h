#include "Shape.h"
#include "Vertex.h"
#include "Triangle.h"

class Polygon: Shape{
public:
	Polygon();
	Polygon(float r, float g, float b, Vertex *vertices, int verticesLength, Triangle *triangles, int trianglesLength);

	//instance methods
	Color getColor();
	float hit(Ray ray);

private:
	float r;
	float g;
	float b;
	Vertex *vertices;
	Triangle *triangles;
	int verticesLength;
	int trianglesLength;
};