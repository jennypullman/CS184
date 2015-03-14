#include "Polygon.h"

class Sphere : public Shape {
public: 
	Sphere();
	Sphere(Material material, float cx, float cy, float cz, float rad);

	//instance methods
	Material getMaterial();
	float hit(Ray ray);
	float getCenterX();
	float getCenterY();
	float getCenterZ();
	float getRadius();
	Point getMostRecentHitPoint();
	void print();

private:
	Material material;   // Material of sphere
	float cx;		// Center x
	float cy;		// Center y
	float cz;		// Center z
	float rad;		// radius
	Point mostRecentHitPoint();
	
};