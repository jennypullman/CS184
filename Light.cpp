#include "Light.h"
Light::Light(){
	x, y, z, r, g, b = 0.0;
	isDir = false;
	activated = false;
}

Light::Light(float x, float y, float z, float r, float g, float b, bool isDir){
	this->x = x;
	this->y = y;
	this->z = z;
	this->r = r;
	this->g = g;
	this->b = b;
	this->isDir = isDir;
	this->lightVector;
	activated = true;
}

Color Light::getColor(){
	return Color(r, g, b);
}

Vector3 Light::getLightVector(float x, float y, float z){
	if (isDir){
		this->lightVector = new Vector3(-1*this->x, -1*this->y, -1*this->z);
		(*this->lightVector).normalize();
	}
	else {
		this->lightVector = new Vector3(this->x - x, this->y - y, this->z - z);
		(*this->lightVector).normalize();
	}
	return *this->lightVector;
}
	
Vector3 Light::getReflectionVector(Vector3 n){
	float tmpScalar;
	try{
		
		tmpScalar = 2*Vector3::dot(n, *lightVector);
		Vector3 tmp = Vector3::add(Vector3::scalarMultiply(*lightVector,-1.0), Vector3::scalarMultiply(n, tmpScalar));
		tmp.normalize();
		return tmp;
	}
	catch (char *exception){
		cout << exception;
	}
}

bool Light::IsDirectional(){
	return isDir;
}

bool Light::IsActivated(){
	return activated;
}

void Light::scaleLocation(float scalar){
	x = x*scalar;
	y = y*scalar;
	z = z*scalar;
}