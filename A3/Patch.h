#include "Triangle.h"

class Patch{
public:
	Patch();
	Patch(Point p1, Point p2, Point p3, Point p4);

	//instance methods
	Point getP1();
	Point getP2();
	Point getP3();
	Point getP4();

private:
	Point p1, p2, p3, p4;
};