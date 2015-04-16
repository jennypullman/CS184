#include <iostream>
using namespace std;
#include <stdlib.h>
#include <math.h>

class Point{
public:
	Point();
	Point(float x, float y, float z); //Point defined by coords

	//instance methods
	float getX();
	float getY();
	float getZ();
	float getDistance(Point p);
	void print();
	bool equals(Point p);

private:
	float x;
	float y;
	float z;
};
