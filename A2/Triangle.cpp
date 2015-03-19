#include "Triangle.h"
#include <stdlib.h>

Triangle::Triangle() {
};
Triangle::Triangle(Material mat, Transformation trans, Vertex vert1, Vertex vert2, Vertex vert3){
	this->material = mat;
	this->vert1 = vert1;
	this->vert2 = vert2;
	this->vert3 = vert3;

	std::cout << "Vert 1: (" << vert1.getX() << ", " << vert1.getY() << ", " << vert1.getZ() << ") \n";			
	std::cout << "Vert 2: (" << vert2.getX() << ", " << vert2.getY() << ", " << vert2.getZ() << ") \n";	
	std::cout << "Vert 3: (" << vert3.getX() << ", " << vert3.getY() << ", " << vert3.getZ() << ") \n";	

	// Vector3 vec1 = Vector3(vert1.getX()-vert2.getX(), vert1.getY()-vert2.getY(), vert1.getZ()-vert2.getZ());
	// Vector3 vec2 = Vector3(vert3.getX()-vert2.getX(), vert3.getY()-vert2.getY(), vert3.getZ()-vert2.getZ());
	Vector3 vec1 = Vector3(vert2.getX()-vert1.getX(), vert2.getY()-vert1.getY(), vert2.getZ()-vert1.getZ());
	Vector3 vec2 = Vector3(vert3.getX()-vert1.getX(), vert3.getY()-vert1.getY(), vert3.getZ()-vert1.getZ());
	Transformation normalTransformation = Transformation::getTranspose(Transformation::getInverse(trans));
	//this->norm = Transformation::vectorMultiply(normalTransformation, Vector3::cross(vec1, vec2));
	this->norm = Vector3::cross(vec1, vec2);
	trans.print();
	std::cout << "Normal : (" << norm.getX() << ", " << norm.getY() << ", " << norm.getZ() << ") \n";
};

Triangle::Triangle(Material mat, Transformation trans, Vertex vert1, Vertex vert2, Vertex vert3, Vector3 norm1, Vector3 norm2, Vector3 norm3){
	this->material = mat;
	this->vert1 = vert1;
	this->vert2 = vert2;
	this->vert3 = vert3;
	this->norm1 = norm1;
	this->norm2 = norm2;
	this->norm3 = norm3;

	Vector3 vec1 = Vector3(vert2.getX()-vert1.getX(), vert2.getY()-vert1.getY(), vert2.getZ()-vert1.getZ());
	Vector3 vec2 = Vector3(vert3.getX()-vert1.getX(), vert3.getY()-vert1.getY(), vert3.getZ()-vert1.getZ());
	Transformation normalTransformation = Transformation::getTranspose(Transformation::getInverse(trans));
	this->norm = Transformation::vectorMultiply(normalTransformation, Vector3::cross(vec1, vec2));
};
//instance methods
Material Triangle::getMaterial(){
	return this->material;
};
float Triangle::hit(Ray ray){

	float epsilon = 0.00001;

	// Vector3 v1 = Vector3(vert1.getX() - vert2.getX(), vert1.getY() - vert2.getY(), vert1.getZ() - vert2.getZ());
	// Vector3 v2 = Vector3(vert3.getX() - vert2.getX(), vert3.getY() - vert2.getY(), vert3.getZ() - vert2.getZ());
	// Vector3 v1 = Vector3(vert2.getX() - vert1.getX(), vert2.getY() - vert1.getY(), vert2.getZ() - vert1.getZ());
	// Vector3 v2 = Vector3(vert3.getX() - vert1.getX(), vert3.getY() - vert1.getY(), vert3.getZ() - vert1.getZ());
	// Vector3 n = Vector3::cross(v1, v2);
	//Lauren add
	// ray.print();
	// std::cout << "Triangle::hit " << std::endl;
	Vector3 n = norm;
	n.normalize();
	float denom = ray.getDirectionX()*n.getX() + ray.getDirectionY()*n.getY() + ray.getDirectionZ()*n.getZ();
	// std::cout << "denom: " << denom << std::endl;
	if (denom == 0){ // ray parallel to surface. no hit.
		// std::cout << "denom was 0, first time";
		return -1.0; //no hit
	}
	float t = (vert1.getX()*n.getX() + vert1.getY()*n.getY() + vert1.getZ()*n.getZ() - 
		(ray.getStartX()*n.getX() + ray.getStartY()*n.getY() + ray.getStartZ()*n.getZ())) /
		denom;
	// std::cout << "t: " << t << std::endl;
	// std::cout << "t = " << t << "\n";
	if (t < epsilon){
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
		// std::cout << "denom was zero, second time";
		return -1.0;
	};
	float beta = (Vector3::dot(vec2, vec3)*Vector3::dot(vec1, vec3) - Vector3::dot(vec3, vec3)*Vector3::dot(vec1, vec2)) / (denom);
	float gamma = (Vector3::dot(vec2, vec3)*Vector3::dot(vec1, vec2) - Vector3::dot(vec2, vec2)*Vector3::dot(vec1, vec3)) / (denom);

	if (beta < epsilon || gamma < epsilon || beta + gamma > 1-epsilon){
		// std::cout << "not inside triangle\n";
		// std::cout << beta;
		// std::cout << "\n";
		// std::cout << gamma;
		// std::cout << "\n";
		return -1.0;
	};
	// std::cout << "Hitpoint: (" << px << ", " << py << ", " << pz << ")\n";
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
Vector3 Triangle::getNormalAtPoint(Point pnt, Vector3 viewVect){
	// TODO may want to get normal by interpolation of normal's at corners
	Vector3 normal = this->norm;
	// if (Vector3::dot(this->norm, viewVect) < 0){
	// 	normal = Vector3(-this->norm.getX(), -this->norm.getY(), -this->norm.getZ());
	// }
	return normal;
}