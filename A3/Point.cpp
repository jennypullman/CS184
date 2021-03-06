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

float Point::getDistance(Point p){
  return sqrt(pow(this->x-p.getX(),2)+pow(this->y-p.getY(),2)+pow(this->z-p.getZ(),2));
}

void Point::print(){
	std::cout << "(" << this->x << ", " << this->y << ", " << this->z << ")" << std::endl;
}

bool Point::equals(Point p) {
	if (x == p.getX()) {
		if (y == p.getY()) {
			if (z == p.getZ()) {
				return true;
			}
		}
	}
	return false;
}
