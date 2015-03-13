#include "Polygon.h"

Polygon::Polygon(){
};

Polygon::Polygon(Material mat, Triangle *triangles, int trianglesLength){
	this->material = mat;
	this->triangles = new Triangle[trianglesLength];
	for (int i = 0; i < trianglesLength; i++){
		this->triangles[i] = triangles[i];
	}

	this->trianglesLength = trianglesLength;
};
	//instance methods
Material Polygon::getMaterial(){
	return this->material;
};
float Polygon::hit(Ray ray){
	float t = -1.0;
	for (int i = 0; i < this->trianglesLength; i++){
		float triangleT = this->triangles[i].hit(ray);
		if (t < 0.0 || (triangleT >= 0.0 && triangleT < t)){
			t = triangleT;
		};
	};
	return t;
};

void Polygon::print(){
	for (int i = 0; i < trianglesLength; i++) {
		std::cout << "Triangle ";
		std::cout << i;
		std::cout << ": ";
		triangles[i].print();
	}
};