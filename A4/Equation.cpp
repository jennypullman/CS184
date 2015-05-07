#include "Equation.h"

Equation::Equation(){};

Equation::Equation(float radius, float theta, float phi, float xc, float yc, float zc){
	this->r = radius;
	this->theta = theta;
	this->phi = phi;
	this->xc = xc;
	this->yc = yc;
	this->zc = zc;
	this->cosPhi = cos(phi);
	this->cosTheta = cos(theta);
	this->sinPhi = sin(phi);
	this->sinTheta = sin(theta);
}

float Equation::getX(float t){
	return -this->r*cos(t)*this->sinPhi + this->r*sin(t)*this->cosTheta*this->cosPhi + this->xc;
}

float Equation::getY(float t){
	return this->r*cos(t)*this->cosPhi + this->r*sin(t)*this->cosTheta*this->sinPhi + this->yc;
}

float Equation::getZ(float t){
	return -this->r*sin(t)*this->sinTheta + this->zc;
}