#include "Triangle.h"

Triangle::Triangle() {
};
Triangle::Triangle(Material mat, Vertex vert1, Vertex vert2, Vertex vert3){
	this->material = mat;
	this->vert1 = vert1;
	this->vert2 = vert2;
	this->vert3 = vert3;
};

Triangle::Triangle(Material mat, Vertex vert1, Vertex vert2, Vertex vert3, Vector3 norm1, Vector3 norm2, Vector3 norm3){
	this->material = mat;
	this->vert1 = vert1;
	this->vert2 = vert2;
	this->vert3 = vert3;
	this->norm1 = norm1;
	this->norm2 = norm2;
	this->norm3 = norm3;
};
//instance methods
Material Triangle::getMaterial(){
	return this->material;
};
float Triangle::hit(Ray ray){

	Vector3 v1 = Vector3(vert1.getX() - vert2.getX(), vert1.getY() - vert2.getY(), vert1.getZ() - vert2.getZ());
	Vector3 v2 = Vector3(vert3.getX() - vert2.getX(), vert3.getY() - vert2.getY(), vert3.getZ() - vert2.getZ());
	Vector3 n = Vector3::cross(v1, v2);
	float denom = ray.getDirectionX()*n.getX() + ray.getDirectionY()*n.getY() + ray.getDirectionZ()*n.getZ();
	if (denom == 0){
		std::cout << "denom was 0, first time";
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
	Vector3 vec2 = Vector3(vert2.getX() - vert1.getX(), vert2.getY() - vert1.getY(), vert2.getZ() - vert1.getZ());
	Vector3 vec3 = Vector3(vert3.getX() - vert1.getX(), vert3.getY() - vert1.getY(), vert3.getZ() - vert1.getZ());

	//denom = Vector3::dot(vec1, vec1)*Vector3::dot(vec2, vec2) - Vector3::dot(vec1, vec2)*Vector3::dot(vec2, vec1);
	denom = Vector3::dot(vec2, vec3)*Vector3::dot(vec2, vec3)-Vector3::dot(vec2,vec2)*Vector3::dot(vec3,vec3);
	if (denom == 0){
		//figure out when this is the case
		std::cout << "denom was zero, second time";
		return -1.0;
	};
	float beta = (Vector3::dot(vec2, vec3)*Vector3::dot(vec1, vec3) - Vector3::dot(vec3, vec3)*Vector3::dot(vec1, vec2)) / (denom);
	float gamma = (Vector3::dot(vec2, vec3)*Vector3::dot(vec1, vec2) - Vector3::dot(vec2, vec2)*Vector3::dot(vec1, vec3)) / (denom);

	if (beta < 0 || gamma < 0 || beta + gamma > 1){
		std::cout << "not inside triangle\n";
		std::cout << beta;
		std::cout << "\n";
		std::cout << gamma;
		std::cout << "\n";
		return -1.0;
	};
	this->mostRecentHitPoint = Point(px, py, pz);
	return t;
};

Point Triangle::getMostRecentHitPoint(){
	return this->mostRecentHitPoint;
}

void Triangle::print(){
	std::cout << "Vertices = (";
	std::cout << this->vert1.getX();
	std::cout << ",";
	std::cout << this->vert1.getY();
	std::cout << ","; 
	std::cout << this->vert1.getZ();
	std::cout << "), (";
	std::cout << this->vert2.getX();
	std::cout << ",";
	std::cout << this->vert2.getY();
	std::cout << ","; 
	std::cout << this->vert2.getZ();
	std::cout << "), (";
	std::cout << this->vert3.getX();
	std::cout << ",";
	std::cout << this->vert3.getY();
	std::cout << ","; 
	std::cout << this->vert3.getZ();
	std::cout << ")\n";
}