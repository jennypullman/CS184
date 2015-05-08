#include "Point.h"
#include <cmath>

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

float Point::distToPt(Point p) {
	float diffX = (p.getX()-x);
	float diffY = (p.getY()-y);
	float diffZ = (p.getZ()-z);
	float temp = diffX*diffX + diffY*diffY + diffZ*diffZ;

	return sqrt(temp);
}

void Point::print(){
	std::cout << "Point: (" << this->x << ", " << this->y << ", " << this->z << ")\n";
} 