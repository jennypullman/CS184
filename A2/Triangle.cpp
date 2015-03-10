#include "Triangle.h";

Triangle::Triangle() {
	this->r, this->g, this->b = 0.0;
	this.vertices = nullptr;
};
Triangle::Triangle(float r, float g, float b, Vertex *vertices){
	this->r = r;
	this->g = g;
	this->b = b;
	this->vertices = vertices;
};

//instance methods
Color Triangle::getColor(){

};
float Triangle::hit(Ray ray){
};