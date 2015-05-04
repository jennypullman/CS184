#include "Point.h"

class UVPoint{
public:
	UVPoint();
	UVPoint(float u, float v); //Point defined by coords

	//instance methods
	float getU();
	float getV();
	void print();

private:
	float u;
	float v;
};
