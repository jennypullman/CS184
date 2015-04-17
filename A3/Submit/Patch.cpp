#include "Patch.h"

Patch::Patch(){
}

Patch::Patch(Point p1, Point p2, Point p3, Point p4, Vector3 sn1, Vector3 sn2, Vector3 sn3, Vector3 sn4, Vector3 fn1, Vector3 fn2, Vector3 fn3, Vector3 fn4){
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->p4 = p4;
	this->sn1 = sn1;
	this->sn2 = sn2;
	this->sn3 = sn3;
	this->sn4 = sn4;
	this->fn1 = fn1;
	this->fn2 = fn2;
	this->fn3 = fn3;
	this->fn4 = fn4;
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

Vector3 Patch::getSN1(){
	return this->sn1;
}

Vector3 Patch::getSN2(){
	return this->sn2;
}

Vector3 Patch::getSN3(){
	return this->sn3;
}

Vector3 Patch::getSN4(){
	return this->sn4;
}

Vector3 Patch::getFN1(){
	return this->fn1;
}

Vector3 Patch::getFN2(){
	return this->fn2;
}

Vector3 Patch::getFN3(){
	return this->fn3;
}

Vector3 Patch::getFN4(){
	return this->fn4;
}