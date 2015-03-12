#include "Light.h"

class PointLight : Light {
public:
	PointLight();
	PointLight(float x, float y, float z, float r, float g, float b, float falloff);

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
	float falloff;
	Vector3 *lightVector;
	bool activated;
};