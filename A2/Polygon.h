#include "Triangle.h"

class Polygon: public Shape{
public:
	Polygon();
	Polygon(Material mat, Triangle *triangles, int trianglesLength);

	//instance methods
	Material getMaterial();
	float hit(Ray ray);
	void print();
	Point getMostRecentHitPoint();

private:
	Material material;
	Triangle *triangles;
	int trianglesLength;
	Triangle mostRecentHitTriangle;
};