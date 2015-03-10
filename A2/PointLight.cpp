#include "PointLight.h"

PointLight::PointLight(){
	x, y, z, r, g, b = 0.0;
	activated = false;
}

PointLight::PointLight(float x, float y, float z, float r, float g, float b){
	this->x = x;
	this->y = y;
	this->z = z;
	this->r = r;
	this->g = g;
	this->b = b;
	this->lightVector;
	activated = true;
}

Color PointLight::getColor(){
	return Color(r, g, b);
}

Vector3 PointLight::getLightVector(float x, float y, float z){
	this->lightVector = new Vector3(this->x - x, this->y - y, this->z - z);
	(*this->lightVector).normalize();
	return *this->lightVector;
}

Vector3 PointLight::getReflectionVector(Vector3 n){
	float tmpScalar;
	try{

		tmpScalar = 2 * Vector3::dot(n, *lightVector);
		Vector3 tmp = Vector3::add(Vector3::scalarMultiply(*lightVector, -1.0), Vector3::scalarMultiply(n, tmpScalar));
		tmp.normalize();
		return tmp;
	}
	catch (char *exception){
		cout << exception;
	}
}

bool PointLight::IsActivated(){
	return activated;
}

void PointLight::scaleLocation(float scalar){
	x = x*scalar;
	y = y*scalar;
	z = z*scalar;
}