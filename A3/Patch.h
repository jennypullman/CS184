#include "Triangle.h"

class Patch{
public:
	Patch();
	Patch(Point p1, Point p2, Point p3, Point p4, Vector3 sn1, Vector3 sn2, Vector3 sn3, Vector3 sn4, Vector3 fn1, Vector3 fn2, Vector3 fn3, Vector3 fn4);

	//instance methods
	Point getP1();
	Point getP2();
	Point getP3();
	Point getP4();
	Vector3 getSN1();
	Vector3 getSN2();
	Vector3 getSN3();
	Vector3 getSN4();
	Vector3 getFN1();
	Vector3 getFN2();
	Vector3 getFN3();
	Vector3 getFN4();

private:
	Point p1, p2, p3, p4;
	Vector3 sn1, sn2, sn3, sn4, fn1, fn2, fn3, fn4;
};
