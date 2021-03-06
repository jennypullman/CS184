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
	Vector3 getNormalAtPoint(Point pnt);

private:
	Material material;
};