//#include "Color.h"
#include "Camera.h"
#include "DirectedLight.h"
#include "Material.h"

class Shape {
public: 

	//instance methods
	virtual Material getMaterial() = 0;
	virtual float hit(Ray ray) = 0;
	virtual void print() = 0;

private:
	Material material;
};