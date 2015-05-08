#include <math.h>

class Equation{
public:
	Equation();
	Equation(float radius, float theta, float phi, float xc, float yc, float zc);

	//instance methods
	float getX(float t);
	float getY(float t);
	float getZ(float t);

private:
	float r, theta, phi, xc, yc, zc, cosPhi, cosTheta, sinPhi, sinTheta;
};