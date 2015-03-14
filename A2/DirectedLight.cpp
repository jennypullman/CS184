#include "DirectedLight.h"

DirectedLight::DirectedLight(){
	x, y, z, r, g, b = 0.0;
	activated = false;
}

DirectedLight::DirectedLight(float x, float y, float z, float r, float g, float b){
	this->x = x;
	this->y = y;
	this->z = z;
	this->r = r;
	this->g = g;
	this->b = b;
	this->lightVector;
	activated = true;
}

Color DirectedLight::getColor(){
	return Color(r, g, b);
}

Vector3 DirectedLight::getLightVector(float x, float y, float z){
	this->lightVector = new Vector3(-1*this->x, -1*this->y, -1*this->z);
	(*this->lightVector).normalize();
	return *this->lightVector;
}
	
Vector3 DirectedLight::getReflectionVector(Vector3 n){
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

bool DirectedLight::IsActivated(){
	return activated;
}

void DirectedLight::scaleLocation(float scalar){
	x = x*scalar;
	y = y*scalar;
	z = z*scalar;
}

Color DirectedLight::getShadingOnObject(Material shp_mat, Point pnt){
	//TO DO lauren
	return Color();
}