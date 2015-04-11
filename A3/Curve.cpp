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

Point Curve::computeDecasteljau(float u){
	Point mid1 = Point((1-u)*c1.getX()+u*c2.getX(),
					(1-u)*c1.getY()+u*c2.getY(),
					(1-u)*c1.getZ()+u*c2.getZ());
	Point mid2 = Point((1-u)*c2.getX()+u*c3.getX(),
					(1-u)*c2.getY()+u*c3.getY(),
					(1-u)*c2.getZ()+u*c3.getZ());
	Point mid3 = Point((1-u)*c3.getX()+u*c4.getX(),
					(1-u)*c3.getY()+u*c4.getY(),
					(1-u)*c3.getZ()+u*c4.getZ());

	Point mid4 = Point((1-u)*mid1.getX()+u*mid2.getX(),
					(1-u)*mid1.getY()+u*mid2.getY(),
					(1-u)*mid1.getZ()+u*mid2.getZ());
	Point mid5 = Point((1-u)*mid2.getX()+u*mid3.getX(),
					(1-u)*mid2.getY()+u*mid3.getY(),
					(1-u)*mid2.getZ()+u*mid3.getZ());

	return Point((1-u)*mid4.getX()+u*mid5.getX(),
					(1-u)*mid4.getY()+u*mid5.getY(),
					(1-u)*mid4.getZ()+u*mid5.getZ());		
}

void Curve::print(){
	std::cout << "Points 1-4: ";
	this->c1.print();
	std::cout << " ";
	this->c2.print();
	std::cout << " ";
	this->c3.print();
	std::cout << " ";
	this->c4.print();
	std::cout << "\n";
}