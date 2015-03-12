#include <iostream>
using namespace std;
//#include "Color.h"
#include "Vector3.h"
#include "Image.h"

class Light {
public:

	virtual Color getColor() = 0;
	virtual Vector3 getLightVector(float x, float y, float z) = 0;
	virtual Vector3 getReflectionVector(Vector3 n) = 0;
	virtual bool IsActivated() = 0;
	virtual void scaleLocation(float scalar) = 0;
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