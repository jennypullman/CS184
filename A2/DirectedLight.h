#include "PointLight.h"

class DirectedLight : public Light {
public:
	DirectedLight();
	DirectedLight(float x, float y, float z, float r, float g, float b);

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
	Vector3 *lightVector;
	bool activated;
};