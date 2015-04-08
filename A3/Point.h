#include <iostream>
using namespace std;
#include <stdlib.h>

class Point{
public:
	Point();
	Point(float x, float y, float z); //Point defined by coords

	//instance methods
	float getX();
	float getY();
	float getZ();
	void print();

private:
	float x;
	float y;
	float z;
};