#include "AmbientLight.h"

class PointLight : public Light {
public:
	PointLight();
	PointLight(float x, float y, float z, float r, float g, float b, int falloff);

	Color getColor();
	Vector3 getLightVector(float x, float y, float z);
	Vector3 getReflectionVector(Vector3 n);
	bool IsActivated();
	void scaleLocation(float scalar);
	Color getShadingOnObject(Material shp_mat, Point pnt, Vector3 normal, Vector3 view);
private:
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
	int falloff;
	Vector3 *lightVector;
	bool activated;
};