#include "Surface.h"

Surface::Surface(){
	c1 = c2 = c3 = c4 = Curve();
}

Surface::Surface(Curve c1, Curve c2, Curve c3, Curve c4){
	this->c1 = c1;
	this->c2 = c2;
	this->c3 = c3;
	this->c4 = c4;
}

Point Surface::computeBezier(float u, float v){
	Point cp1 = this->c1.computeDecasteljau(u);
	Point cp2 = this->c2.computeDecasteljau(u);
	Point cp3 = this->c3.computeDecasteljau(u);
	Point cp4 = this->c4.computeDecasteljau(u);
	Curve c = Curve(cp1, cp2, cp3, cp4);
	return c.computeDecasteljau(v);
}

Patch Surface::determinePatch(float u, float v, float du, float dv){
	//return patch starting from u,v, and going clockwise
	if (u < 0 || v < 0 || du < 0 || dv < 0 || u+du > 1 || v+dv >1){
		// cout << (u < 0) << (v < 0) << (du < 0) << (dv < 0) << (u+du >= 1) << (v+dv >= 1) << endl;
		// cout << "v+dv: " << v+dv << endl;
		cout << "Incorrect arguments in determinePatch\n";
		//TO DO 
	}
	return Patch(this->computeBezier(u,v),this->computeBezier(u,v+dv),
				this->computeBezier(u+du,v+dv), this->computeBezier(u+du,v));
}

void Surface::print(){
	std::cout << "Curve 1: ";
	this->c1.print();
	std::cout << "Curve 2: ";
	this->c2.print();
	std::cout << "Curve 3: ";
	this->c3.print();
	std::cout << "Curve 4: ";
	this->c4.print();
}