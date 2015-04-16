#include "Point.h"

Point::Point(){
	this->x, this->y, this->z = 0.0;
}

Point::Point(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

float Point::getX(){
	return this->x;
}

float Point::getY(){
	return this->y;
}

float Point::getZ(){
	return this->z;
}

void Point::print(){
	std::cout << "(" << this->x << ", " << this->y << ", " << this->z << ")" << std::endl;
}