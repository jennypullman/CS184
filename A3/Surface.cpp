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