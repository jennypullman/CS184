#include "AmbientLight.h"

AmbientLight::AmbientLight(){
	this->activated = false;
}

AmbientLight::AmbientLight(float r, float g, float b){
	this->r = r;
	this->g = g;
	this->b = b;
	this->activated = true;
}

Light::Light(){

}

Color Light::getColor(){
	return Color(this->r, this->g, this->b);
}

Vector3 Light::getLightVector(float x, float y, float z){
	return Vector3();
}

Vector3 Light::getReflectionVector(Vector3 n){
	return Vector3();
}

bool Light::IsActivated(){
	return this->activated;
}

void Light::scaleLocation(float scalar){

}

Color Light::getShadingOnObject(Material shp_mat, Point pnt, Vector3 normal, Vector3 view){
	//TO DO lauren
	return Color();
}