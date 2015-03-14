#include <iostream>
using namespace std;
//#include "Color.h"
#include "Image.h"
#include "Material.h"
#include "ViewPlane.h"

class Light {
public:

	Light();
	Color getColor();
	Vector3 getLightVector(float x, float y, float z);
	Vector3 getReflectionVector(Vector3 n);
	bool IsActivated();
	void scaleLocation(float scalar);
	Color getShadingOnObject(Material shp_mat, Point pnt);
private:
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
	Vector3 *lightVector;
	bool activated;
};