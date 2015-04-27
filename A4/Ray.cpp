#include "Ray.h"

Ray::Ray(){
}

Ray::Ray(float startx, float starty, float startz, float dirx, float diry, float dirz){
	this->startx = startx;
	this->starty = starty;
	this->startz = startz;
	this->dirx = dirx;
	this->diry = diry;
	this->dirz = dirz;
}

float Ray::getStartX(){
	return this->startx;
}

float Ray::getStartY(){
	return this->starty;
}

float Ray::getStartZ(){
	return this->startz;
}

float Ray::getDirectionX(){
	return this->dirx;
}

float Ray::getDirectionY(){
	return this->diry;
}

float Ray::getDirectionZ(){
	return this->dirz;
}

void Ray::print(){
	std::cout << "Printing Ray...\n(";
	std::cout << this->startx;
	std::cout << ", ";
	std::cout << this->starty;
	std::cout << ", ";
	std::cout << this->startz;
	std::cout << ") + (";
	std::cout << this->dirx;
	std::cout << ", ";
	std::cout << this->diry;
	std::cout << ", ";
	std::cout << this->dirz;
	std::cout << ")t\n";

}