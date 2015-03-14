//#include "Color.h"
#include "Camera.h"
#include "DirectedLight.h"

class Shape {
public: 

	Shape();

	//instance methods
	Material getMaterial();
	float hit(Ray ray);
	void print();
	Point getMostRecentHitPoint();

private:
	Material material;
};