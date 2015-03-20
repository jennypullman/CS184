#include "Triangle.h"

class Polygon: public Shape{
public:
	Polygon();
	Polygon(Material mat, Triangle *triangles, int trianglesLength);

	//instance methods
	Material getMaterial();
	float hit(Ray ray);
	Point getMostRecentHitPoint();
	void print();
	Vector3 getNormalAtPoint(Point pnt, Vector3 viewVect);

private:
	Material material;
	Triangle *triangles;
	int trianglesLength;
	Triangle mostRecentHitTriangle;
};