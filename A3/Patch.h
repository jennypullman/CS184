#include "Point.h"

class Patch{
public:
	Patch();
	Patch(Point p1, Point p2, Point p3, Point p4);

private:
	Point p1, p2, p3, p4;
};