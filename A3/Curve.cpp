#include "Curve.h"

Curve::Curve(){
	c1 = c2 = c3 = c4 = Point();
}

Curve::Curve(Point c1, Point c2, Point c3, Point c4){
	this->c1 = c1;
	this->c2 = c2;
	this->c3 = c3;
	this->c4 = c4;
}