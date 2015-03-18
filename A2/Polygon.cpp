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
		float epsilon = 0.0001;
		if (t < epsilon || (triangleT >= epsilon && triangleT < t)){
			t = triangleT;
			this->mostRecentHitTriangle = this->triangles[i];
		};
	};
	return t;
};


Point Polygon::getMostRecentHitPoint(){
	return this->mostRecentHitTriangle.getMostRecentHitPoint();
}

void Polygon::print(){
	for (int i = 0; i < trianglesLength; i++) {
		std::cout << "Triangle ";
		std::cout << i;
		std::cout << ": ";
		triangles[i].print();
	}
};


Vector3 Polygon::getNormalAtPoint(Point pnt, Vector3 viewVect){
	return this->mostRecentHitTriangle.getNormalAtPoint(pnt, viewVect);
}