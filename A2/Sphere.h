#include "Polygon.h"

class Shpere : Shape {
public: 
	Sphere();
	Sphere(float r, float g, float b, float cx, float, float cy, float cz, float rad);

	//instance methods
	Color getColor();
	float hit(Ray ray);
	float getCenterX();
	float getCenterY();
	float getCenterZ();
	float getRadius();

private:
	float r;
	float g;
	float b;
	float cx;		// Center x
	float cy;		// Center y
	float cz;		// Center z
	float rad;		// radius
	
};