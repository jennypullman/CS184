#include "Patch.h"

Patch::Patch(){
}

Patch::Patch(Point p1, Point p2, Point p3, Point p4, Vector3 n1, Vector3 n2, Vector3 n3, Vector3 n4){
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->p4 = p4;
	this->n1 = n1;
	this->n2 = n2;
	this->n3 = n3;
	this->n4 = n4;
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

Vector3 Patch::getN1(){
	return this->n1;
}

Vector3 Patch::getN2(){
	return this->n2;
}

Vector3 Patch::getN3(){
	return this->n3;
}

Vector3 Patch::getN4(){
	return this->n4;
}