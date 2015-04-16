#include "Curve.h"

class Surface{
public:
	Surface();
	Surface(Curve c1, Curve c2, Curve c3, Curve c4); //Surface defined by curves

	//instance methods
	Point computeBezier(float u, float v);
	Vector3 computeNormal(float u, float v);
	Vector3 computeNormal(Point p1, Point p2, Point p3, Point p4);
	Patch determinePatch(float u, float v, float du, float dv);
	void print();

private:
	Curve c1;
	Curve c2;
	Curve c3;
	Curve c4;
	bool drawn = false;
};