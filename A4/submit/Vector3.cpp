#include "Vector3.h"

Vector3::Vector3(){
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
}
Vector3::Vector3(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}
float Vector3::getX(){
	return x;
}
float Vector3::getY(){
	return y;
}
float Vector3::getZ(){
	return z;
}

void Vector3::normalize() {
	float magnitude = getMagnitude();
	x = x / magnitude;
	y = y / magnitude;
	z = z / magnitude;
}

float Vector3::getMagnitude() {
	return sqrt(x*x + y*y + z*z);
}

Vector3 Vector3::add(Vector3 vec1, Vector3 vec2){
	return Vector3(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}
	//return vec1 - vec2
Vector3 Vector3::subtract(Vector3 vec1, Vector3 vec2){
	return Vector3(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}
float Vector3::dot(Vector3 vec1, Vector3 vec2){
	return vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
}
	//return vec1 x vec2
Vector3 Vector3::cross(Vector3 vec1, Vector3 vec2){
	return Vector3(vec1.y*vec2.z - vec1.z*vec2.y, vec1.z*vec2.x - vec1.x*vec2.z, vec1.x*vec2.y - vec1.y*vec2.x);
}
Vector3 Vector3::scalarMultiply(Vector3 vec, float i){
	return Vector3(vec.x*i, vec.y*i, vec.z*i);
}
Vector3 Vector3::scalarDivide(Vector3 vec, float i){
	if (i != 0) {
		return Vector3(vec.x / i, vec.y / i, vec.z / i);
	}
	throw std::overflow_error("Divide by zero error.");
}

void Vector3::print(){
	std::cout << "Printing Vector...\n(";
	std::cout << this->x;
	std::cout << ", ";
	std::cout << this->y;
	std::cout << ", ";
	std::cout << this->z;
	std::cout << ")\n";
}