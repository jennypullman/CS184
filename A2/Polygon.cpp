#include "Polygon.h";

Polygon::Polygon(){
	this->r, this->g, this->b = 0.0;
	this->vertices = nullptr;
	this->verticesLength = 0;
	this->triangles = nullptr;
	this->trianglesLength = 0;
};

Polygon::Polygon(float r, float g, float b, Vertex *vertices, int verticesLength, Triangle *triangles, int trianglesLength){
	this->r = r;
	this->g = g;
	this->b = b;
	this->vertices = vertices;
	this->verticesLength = verticesLength;
	this->triangles = triangles;
	this->trianglesLength = trianglesLength;
};
	//instance methods
Color Polygon::getColor(){
	return Color(this->r, this->g, this->b);
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