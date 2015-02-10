#include <iostream>
using namespace std;
#include "Color.h"
#include "Vector3.h"

class Light {
public:
	Light();
	Light(float x, float y, float z, float r, float g, float b, bool isDir);

	Color getColor();
	Vector3 getLightVector(float x, float y, float z);
	Vector3 getReflectionVector(Vector3 n);
	bool IsDirectional();
private:
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
	bool isDir;
	Vector3 *lightVector;
};