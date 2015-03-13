#include "Ray.h"

class Camera{
public:
	Camera();
	Camera(float x, float y, float z); //Camera defined by position relative to origin (0,0,0)

	//instance methods
	float getX();
	float getY();
	float getZ();

	Ray getRayThroughPixel(float px, float py, float pz); // Returns ray from camera through pixel with center (px,py,pz)

private:
	float x;
	float y;
	float z;
};