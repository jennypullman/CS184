#include "Point.h"

class Vertex : Point {
public:
	Vertex();
	Vertex(float x, float y, float z);

	//instance methods
	float getX();
	float getY();
	float getZ();

private:
	float x;
	float y;
	float z;
};