#include "Ellipsoid.h"


Ellipsoid::Ellipsoid(){

}
/*
float cx, float cy, float cz, float pxx, 
	float pxy, float pxz, float pyx, float pyy, float pyz, float pzx, 
	float pzy, float pzz){
	this->material = material;
	this->cx = cx;
	this->cy = cy;
	this->cz = cz;
	this->pxx = pxx;
	this->pxy = pxy;
	this->pxz = pxz;
	this->pyx = pyx;
	this->pyy = pyy;
	this->pyz = pyz;
	this->pzx = pzx;
	this->pzy = pzy;
	this->pzz = pzz;*/

Ellipsoid::Ellipsoid(Material material, Transformation trans, float cx, float cy, float cz, float r){
	this->material = material;
	this->cx = cx;
	this->cy = cy;
	this->cz = cz;
	this->radius = r;
	this->transformation = trans;
	this->inverseTransformation = Transformation::getInverse(transformation);
}

Material Ellipsoid::getMaterial(){
	return this->material;
}

float Ellipsoid::hit(Ray ray){
	//transform ray
	Vertex vert = Vertex(ray.getStartX(), ray.getStartY(), ray.getStartZ());
	Vector3 vect = Vector3(ray.getDirectionX(), ray.getDirectionY(), ray.getDirectionZ());
	vert = Transformation::transformVertex(this->inverseTransformation, vert);
	vect = Transformation::vectorMultiply(this->inverseTransformation, vect);
	Ray transformedRay = Ray(vert.getX(), vert.getY(), vert.getZ(), 
			vect.getX(), vect.getY(), vect.getZ());
	this->inverseTransformation.print();
	ray.print();

	transformedRay.print();
	//check if hits sphere
	float a, b, c;
	a = transformedRay.getDirectionX()*transformedRay.getDirectionX()+
		transformedRay.getDirectionY()*transformedRay.getDirectionY()+
		transformedRay.getDirectionZ()*transformedRay.getDirectionZ();
	b = 2*transformedRay.getDirectionX()*(transformedRay.getStartX()-this->cx)+
		2*transformedRay.getDirectionY()*(transformedRay.getStartY()-this->cy)+
		2*transformedRay.getDirectionZ()*(transformedRay.getStartZ()-this->cz);
	c = transformedRay.getStartX()*transformedRay.getStartX()+transformedRay.getStartY()*
		transformedRay.getStartY()+transformedRay.getStartZ()*transformedRay.getStartZ()+
		this->cx*this->cx + this->cy*this->cy + this->cz*this->cz -
		2*(transformedRay.getStartX()*this->cx + transformedRay.getStartY()*this->cy + 
		transformedRay.getStartZ()*this->cz) -
		this->radius*this->radius;
		
	std::cout << "a = ";
	std::cout << a;
	std::cout << "\nb = ";
	std::cout << b;
	std::cout << "\nc = ";
	std::cout << c;
	std::cout << "\n";

	float dividend = b*b - 4*a*c;
	if (dividend < 0.0){
		return -1.0;
	}
	dividend = sqrt(dividend);
	//TO DO
	//will a ever be 0???
	float t1 = (-b + dividend)/(2*a);
	float t2 = (-b - dividend)/(2*a);
	float hitx, hity,hitz;
	/*std::cout << "transformation: ";
	this->transformation.print();
	std::cout << "transformedRay: (";
	std::cout << transformedRay.getStartX();
	std::cout << ", ";
	std::cout << transformedRay.getStartY();
	std::cout << ", ";
	std::cout << transformedRay.getStartZ();
	std::cout << "), (";
	std::cout << transformedRay.getDirectionX();
	std::cout << ", ";
	std::cout << transformedRay.getDirectionY();
	std::cout << ", ";
	std::cout << transformedRay.getDirectionZ();
	std::cout << ")\n";*/


	if (t1 >= 0.0) {
		if (t2 >= 0.0 && t2 < t1){
			hitx = transformedRay.getStartX() + t2*transformedRay.getDirectionX();
			hity = transformedRay.getStartY() + t2*transformedRay.getDirectionY();
			hitz = transformedRay.getStartZ() + t2*transformedRay.getDirectionZ();
			this->mostRecentHitPoint = Transformation::transformPoint(this->transformation, Point(hitx, hity, hitz));
			return t2;
		}
		hitx = transformedRay.getStartX() + t1*transformedRay.getDirectionX();
		hity = transformedRay.getStartY() + t1*transformedRay.getDirectionY();
		hitz = transformedRay.getStartZ() + t1*transformedRay.getDirectionZ();
		this->mostRecentHitPoint = Transformation::transformPoint(this->transformation, Point(hitx, hity, hitz));
		return t1;
	}
	std::cout << transformedRay.getStartZ();
	std::cout << transformedRay.getDirectionZ();
	std::cout << "here\n\n\n\n\n\n\n\n";
	hitx = transformedRay.getStartX() + t2*transformedRay.getDirectionX();
	hity = transformedRay.getStartY() + t2*transformedRay.getDirectionY();
	hitz = transformedRay.getStartZ() + t2*transformedRay.getDirectionZ();
	this->mostRecentHitPoint = Transformation::transformPoint(this->transformation, Point(hitx, hity, hitz));
	//this->mostRecentHitPoint = Point(transformedRay.getDirectionX(), transformedRay.getDirectionY(), transformedRay.getDirectionZ());
	//this->mostRecentHitPoint = Point(1,1,3);
	return t2;
}

float Ellipsoid::getCenterX(){
	return this->cx;
}

float Ellipsoid::getCenterY(){
	return this->cy;
}

float Ellipsoid::getCenterZ(){
	return this->cz;
}

float Ellipsoid::getOriginalRadius(){
	return this->radius;
}

/*
float Ellipsoid::getXRadius(){
	return sqrt(pow(this->cx-pxx),2)+pow(this->cy-pxy),2)+pow(this->cz-pxz));
}

float Ellipsoid::getYRadius(){
	return sqrt(pow(this->cx-pyx),2)+pow(this->cy-pyy),2)+pow(this->cz-pyz));
}

float Ellipsoid::getZRadius(){
	return sqrt(pow(this->cx-pzx),2)+pow(this->cy-pzy),2)+pow(this->cz-pzz));
}*/

Point Ellipsoid::getMostRecentHitPoint(){
	return this->mostRecentHitPoint;
}

Vector3 Ellipsoid::getNormalAtPoint(Point pnt){
	Vector3 normal = Vector3(pnt.getX()-this->cx, pnt.getY()-this->cy, pnt.getZ()-this->cz);
	normal = Transformation::vectorMultiply(this->transformation, normal);
	//normal.normalize();
	return normal;	
}

void Ellipsoid::print(){

}