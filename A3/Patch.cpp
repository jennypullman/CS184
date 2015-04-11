#include "Patch.h"

Patch::Patch(){
}

Patch::Patch(Point p1, Point p2, Point p3, Point p4){
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->p4 = p4;
}

Point Patch::getP1(){
	return this->p1;
}

Point Patch::getP2(){
	return this->p2;
}

Point Patch::getP3(){
	return this->p3;
}

Point Patch::getP4(){
	return this->p4;
}