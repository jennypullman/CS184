#include "Light.h"

Light::Light(){

}

Color Light::getColor(){
	return Color();
}

Vector3 Light::getLightVector(float x, float y, float z){
	return Vector3();
}

Vector3 Light::getReflectionVector(Vector3 n){
	return Vector3();
}

bool Light::IsActivated(){
	return false;
}

void Light::scaleLocation(float scalar){
}

Color Light::getShadingOnObject(Material shp_mat, Point pnt, Vector3 normal, Vector3 view){
	return Color();
}