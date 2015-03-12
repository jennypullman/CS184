#include <iostream>
using namespace std;
//#include "Color.h"
#include "Vector3.h"
#include "Image.h";

class Light {
public:
	Light();
	Light(float x, float y, float z, float r, float g, float b);

	Color getColor();
	Vector3 getLightVector(float x, float y, float z);
	Vector3 getReflectionVector(Vector3 n);
	bool IsActivated();
	void scaleLocation(float scalar);
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