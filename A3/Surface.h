#include "Curve.h"

class Surface{
public:
	Surface();
	Surface(Curve c1, Curve c2, Curve c3, Curve c4); //Surface defined by curves

	//instance methods
	void print();

private:
	Curve c1;
	Curve c2;
	Curve c3;
	Curve c4;
	bool drawn = false;
};