#include "Camera.h"

Camera::Camera(){

};

Camera::Camera(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
};

float Camera::getX(){
	return this->x;
}

float Camera::getY(){
	return this->y;
}

float Camera::getZ(){
	return this->z;
}

Ray Camera::getRayThroughPixel(float px, float py, float pz) {
	return Ray(this->x, this->y, this->z, px-this->x, py-this->y, pz-this->z);
};