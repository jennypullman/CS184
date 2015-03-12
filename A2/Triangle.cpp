#include "Triangle.h"

Triangle::Triangle() {
	this->r, this->g, this->b = 0.0;
};
Triangle::Triangle(float r, float g, float b, Vertex *vertices){
	this->r = r;
	this->g = g;
	this->b = b;
	this->vertices = vertices;
};

//instance methods
Color Triangle::getColor(){
	return Color(this->r, this->g, this->b);
};
float Triangle::hit(Ray ray){
	Vertex vert1 = (this->vertices)[0];
	Vertex vert2 = (this->vertices)[1];
	Vertex vert3 = (this->vertices)[2];

	Vector3 v1 = Vector3(vert1.getX() - vert2.getX(), vert1.getY() - vert2.getY(), vert1.getZ() - vert2.getZ());
	Vector3 v2 = Vector3(vert3.getX() - vert2.getX(), vert3.getY() - vert2.getY(), vert3.getZ() - vert2.getZ());
	Vector3 n = Vector3::cross(v1, v2);
	float denom = ray.getDirectionX()*n.getX() + ray.getDirectionY()*n.getY() + ray.getDirectionZ()*n.getZ();
	if (denom == 0){
		return -1.0; //no hit
	}
	float t = (vert1.getX()*n.getX() + vert1.getY()*n.getY() + vert1.getZ()*n.getZ() - 
		(ray.getStartX()*n.getX() + ray.getStartY()*n.getY() + ray.getStartZ()*n.getZ())) /
		denom;
	if (t < 0){
		return t; //no hit
	}

	//point that could intersect the triangle
	float px = ray.getStartX() + t*ray.getDirectionX();
	float py = ray.getStartY() + t*ray.getDirectionY();
	float pz = ray.getStartZ() + t*ray.getDirectionZ();

	Vector3 vec1 = Vector3(px - vert1.getX(), py - vert1.getY(), pz - vert1.getZ());
	Vector3 vec2 = Vector3(vert3.getX() - vert2.getX(), vert3.getY() - vert2.getY(), vert3.getZ() - vert2.getY());
	Vector3 vec3 = Vector3(vert2.getX() - vert1.getX(), vert2.getY() - vert1.getY(), vert2.getZ() - vert1.getZ());

	denom = Vector3::dot(vec1, vec1)*Vector3::dot(vec2, vec2) - Vector3::dot(vec1, vec2)*Vector3::dot(vec2, vec1);
	if (denom == 0){
		//figure out when this is the case
		return -1.0;
	};
	float beta = (Vector3::dot(vec2, vec2)*Vector3::dot(vec3, vec1) - Vector3::dot(vec2, vec1)*Vector3::dot(vec3, vec2)) / (denom);
	float gamma = (Vector3::dot(vec1, vec2)*Vector3::dot(vec3, vec2) - Vector3::dot(vec1, vec2)*Vector3::dot(vec3, vec1)) / (denom);

	if (beta < 0 || gamma < 0 || beta + gamma > 1){
		return -1.0;
	};
	return t;
};