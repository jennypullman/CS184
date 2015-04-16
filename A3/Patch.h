#include "Triangle.h"

class Patch{
public:
	Patch();
	Patch(Point p1, Point p2, Point p3, Point p4, Vector3 n1, Vector3 n2, Vector3 n3, Vector3 n4);

	//instance methods
	Point getP1();
	Point getP2();
	Point getP3();
	Point getP4();
	Vector3 getN1();
	Vector3 getN2();
	Vector3 getN3();
	Vector3 getN4();

private:
	Point p1, p2, p3, p4;
	Vector3 n1, n2, n3, n4;
};
