#include "PointLight.h"

class DirectedLight : Light {
public:
	DirectedLight();
	DirectedLight(float x, float y, float z, float r, float g, float b);

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