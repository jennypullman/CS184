#include "Triangle.h"

class Polygon: Shape{
public:
	Polygon();
	Polygon(Material mat, Triangle *triangles, int trianglesLength);

	//instance methods
	Material getMaterial();
	float hit(Ray ray);
	void print();

private:
	Material material;
	Triangle *triangles;
	int trianglesLength;
};