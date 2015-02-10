#include "Light.h"
#include <iostream>
using namespace std;

Light::Light(){
	x, y, z, r, g, b = 0.0;
	isDir = false;
}

Light::Light(float x, float y, float z, float r, float g, float b, bool isDir){
	this->x = x;
	this->y = y;
	this->z = z;
	this->r = r;
	this->g = g;
	this->b = b;
	this->isDir = isDir;
	lightVector = nullptr;
}

float* Light::getPosition(){
	return new float[] { x, y, z };
}

float* Light::getColor(){
	return new float[] {r, g, b};
}

Vector3 Light::getLightVector(float x, float y, float z){
	Vector3 lightVector;
	if (isDir){
		lightVector = Vector3(-this->x, -this->y, -this->z);
		lightVector.normalize();
	}
	else {
		lightVector = Vector3(x - this->x, y - this->y, z - this->z);
		lightVector.normalize();
	}
}
	
Vector3 Light::getReflectionVector(Vector3 n){
	float tmpScalar;
	try{
		tmpScalar = 2*Vector3::dot(n, *lightVector);
		return Vector3::add(Vector3::scalarMultiply(*lightVector, -1), Vector3::scalarMultiply(n, tmpScalar));
	}
	catch (char *exception){
		cout << exception;
	}
}

bool Light::IsDirectional(){
	return isDir;
}