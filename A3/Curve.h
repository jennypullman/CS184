#include "Point.h"

class Curve{
public:
	Curve();
	Curve(Point c1, Point c2, Point c3, Point c4); //Curve defined by control points

	//instance methods
	void print();

private:
	Point c1;
	Point c2;
	Point c3;
	Point c4;
	bool drawn = false;
};