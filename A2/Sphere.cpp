#include "Sphere.h"

Sphere::Sphere(){

}

Sphere::Sphere(Material material, float cx, float cy, float cz, float rad){
	this->material = material;
	this->cz = cz;
	this->cy = cy;
	this->cz = cz;
	this->rad = rad;
}

Material Sphere::getMaterial(){
	return this->material;
}

float Sphere::getCenterX(){
	return this->cx;
}

float Sphere::getCenterY(){
	return this->cy;
}

float Sphere::getCenterZ(){
	return this->cz;
}

float Sphere::getRadius(){
	return this->rad;
}

float Sphere::hit(Ray ray){
	float a, b, c;
	a = ray.getDirectionX()*ray.getDirectionX()+ray.getDirectionY()*ray.getDirectionY()+ray.getDirectionZ()*ray.getDirectionZ();
	b = 2*ray.getDirectionX()*(ray.getStartX()-this->cx)+
		2*ray.getDirectionY()*(ray.getStartY()-this->cy)+
		2*ray.getDirectionZ()*(ray.getStartZ()-this->cz);
	c = ray.getStartX()*ray.getStartX()+ray.getStartY()*ray.getStartY()+ray.getStartZ()*ray.getStartZ()+
		this->cx*this->cx + this->cy*this->cy + this->cz*this->cz -
		2*(ray.getStartX()*this->cx + ray.getStartY()*this->cy + ray.getStartZ()*this->cz) -
		this->rad*this->rad;
	float dividend = b*b - 4*a*c;
	if (dividend < 0.0){
		return -1.0;
	}
	dividend = sqrt(dividend);
	//TO DO
	//will a ever be 0???
	float t1 = (-b + dividend)/(2*a);
	float t2 = (-b - dividend)/(2*a);
	if (t1 >= 0.0) {
		if (t2 >= 0.0 && t2 < t1){
			return t2;
		}
		return t1;
	}
	return t2;
}

void Sphere::print(){
	std::cout << "Center: (";
	std::cout << this->cx;
	std::cout << ", ";
	std::cout << this->cy;
	std::cout << ", ";
	std::cout << this->cz;
	std::cout << "), Radius = ";
	std::cout << this->rad;
	std::cout << "\n";
}