//#include "Color.h"
#include "Ray.h"
#include "DirectedLight.h"

class Shape {
public: 
	Shape();
	Shape(float r, float g, float b);

	//instance methods
	Color getColor();
	float hit(Ray ray);

private:
	float r;
	float g;
	float b;
};