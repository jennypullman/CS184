#include "Patch.h"

class Curve{
public:
	Curve();
	Curve(Point c1, Point c2, Point c3, Point c4); //Curve defined by control points

	//instance methods
	Point computeDecasteljau(float u);
	Vector3 computeDecNorm(float u);
	void print();
	Point getP1();
	Point getP2();
	Point getP3();
	Point getP4();


private:
	Point c1;
	Point c2;
	Point c3;
	Point c4;
	bool drawn = false;
};