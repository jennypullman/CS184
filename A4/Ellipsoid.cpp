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
	Transformation transformFromUnit = Transformation(cx, cy, cz, 't');
	Point center = Point(0,0,0);
	center = Transformation::transformPoint(trans, center);
	center = Transformation::transformPoint(transformFromUnit, center);
  	transformFromUnit = Transformation::transformMultiply(transformFromUnit,trans);
  	transformFromUnit = Transformation::transformMultiply(transformFromUnit, Transformation(r, r, r, 's'));
  	//transformFromUnit = Transformation::transformMultiply(transformFromUnit, Transformation(r, r, r, 's'));
  	//Transformation tmp = Transformation::transformMultiply(trans, Transformation(r, r, r, 's'));
  	//transformFromUnit = Transformation::transformMultiply(tmp, transformFromUnit);
	this->transformation = transformFromUnit;
	// Point center = Transformation::transformPoint(transformFromUnit, Point(0, 0, 0));
	this->material = material;
	this->cx = center.getX();
	this->cy = center.getY();
	this->cz = center.getZ();
	this->radius = r;
	this->inverseTransformation = Transformation::getInverse(transformation);
	//inverseTransformation.print();
}

Material Ellipsoid::getMaterial(){
	return this->material;
}

float Ellipsoid::hit(Ray ray){
	//inverseTransformation.print();

	/*std::cout << "Center: ";
	std::cout << cx;
	std::cout << ", ";
	std::cout << cy;
	std::cout << ", ";
	std::cout << cz;
	std::cout << ") \n";
	transformation.print();*/

	//transform ray
	Vertex vert = Vertex(ray.getStartX(), ray.getStartY(), ray.getStartZ());
	Vector3 vect = Vector3(ray.getDirectionX(), ray.getDirectionY(), ray.getDirectionZ());
	// std::cout << "start of hit: \n";
	//ray.print();

	vert = Transformation::transformVertex(this->inverseTransformation, vert);
	vect = Transformation::vectorMultiply(this->inverseTransformation, vect);
	Ray transformedRay = Ray(vert.getX(), vert.getY(), vert.getZ(), 
			vect.getX(), vect.getY(), vect.getZ());

	//this->inverseTransformation.print();
	// inverseTransformation.print();
	// transformedRay.print();
	//check if hits sphere
	float a, b, c;
	a = 0.0 + transformedRay.getDirectionX()*transformedRay.getDirectionX()+
		transformedRay.getDirectionY()*transformedRay.getDirectionY()+
		transformedRay.getDirectionZ()*transformedRay.getDirectionZ();
	b = 0.0 + 2*transformedRay.getDirectionX()*transformedRay.getStartX()+
		2*transformedRay.getDirectionY()*transformedRay.getStartY()+
		2*transformedRay.getDirectionZ()*transformedRay.getStartZ();
	c = 0.0 + transformedRay.getStartX()*transformedRay.getStartX()+transformedRay.getStartY()*
		transformedRay.getStartY()+transformedRay.getStartZ()*transformedRay.getStartZ()-
		1;
		
	// std::cout << "a = ";
	// std::cout << a;
	// std::cout << "\nb = ";
	// std::cout << b;
	// std::cout << "\nc = ";
	// std::cout << c;
	// std::cout << "\n";
	
	float dividend = b*b - 4*a*c;
	if (dividend < 0.0 || a == 0.0){
			
		// std::cout << "a = ";
		// std::cout << a;
		// std::cout << "\ndividend = ";
		// std::cout << dividend;
		// std::cout << "\n";
		
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
	//transformedRay.print();

	float epsilon = 0.0001;

	if (t1 < epsilon && t2 < epsilon){

		// std::cout << t1;
		// std::cout << "\n";
		// std::cout << t2;
		// std::cout << "yay\n";
		
		return -1.0;
		
	}
	//transformedRay.print();

	// std::cout << "t1: " << t1 << ", t2: " << t2 << std::endl;

	if (t1 >= epsilon) {
		if (t2 >= epsilon && t2 < t1){
			hitx = ray.getStartX() + t2*ray.getDirectionX();
			hity = ray.getStartY() + t2*ray.getDirectionY();
			hitz = ray.getStartZ() + t2*ray.getDirectionZ();
			//this->mostRecentHitPoint = Transformation::transformPoint(this->transformation, Point(hitx, hity, hitz));
			/*std::cout << "Printing point: ";
			std::cout << hitx;
			std::cout << ", ";
			std::cout << hity;
			std::cout << ", ";
			std::cout << hitz;
			std::cout << "\n";*/
			this->mostRecentHitPoint = Point(hitx, hity, hitz);
			return t2;
		}
		hitx = ray.getStartX() + t1*ray.getDirectionX();
		hity = ray.getStartY() + t1*ray.getDirectionY();
		hitz = ray.getStartZ() + t1*ray.getDirectionZ();
		/*std::cout << "Printing point: ";
		std::cout << hitx;
		std::cout << ", ";
		std::cout << hity;
		std::cout << ", ";
		std::cout << hitz;
		std::cout << "\n";*/
		///this->mostRecentHitPoint = Transformation::transformPoint(this->transformation, Point(hitx, hity, hitz));
		this->mostRecentHitPoint = Point(hitx, hity, hitz);
		return t1;
	}
	//std::cout << transformedRay.getStartZ();
	//std::cout << transformedRay.getDirectionZ();
	//std::cout << "here\n\n\n\n\n\n\n\n";
	hitx = ray.getStartX() + t2*ray.getDirectionX();
	hity = ray.getStartY() + t2*ray.getDirectionY();
	hitz = ray.getStartZ() + t2*ray.getDirectionZ();
	/*std::cout << "Printing point: ";
	std::cout << hitx;
	std::cout << ", ";
	std::cout << hity;
	std::cout << ", ";
	std::cout << hitz;
	std::cout << "\n";*/
	//this->mostRecentHitPoint = Transformation::transformPoint(this->transformation, Point(hitx, hity, hitz));
	//this->mostRecentHitPoint = Point(transformedRay.getDirectionX(), transformedRay.getDirectionY(), transformedRay.getDirectionZ());
	//this->mostRecentHitPoint = Point(1,1,3);
	this->mostRecentHitPoint = Point(hitx, hity, hitz);
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
	pnt = Transformation::transformPoint(inverseTransformation, pnt);
	// Vector3 normal = Vector3(pnt.getX()-this->cx, pnt.getY()-this->cy, pnt.getZ()-this->cz);
	Vector3 normal = Vector3(pnt.getX(), pnt.getY(), pnt.getZ());
	// std::cout << cx << ", " << cy << ", " << cz << std::endl;
		
	// normal = Transformation::vectorMultiply(this->transformation, normal);
	normal = Transformation::vectorMultiply(Transformation::getTranspose(this->inverseTransformation), normal);
	// normal = Transformation::vectorMultiply(Transformation::getTranspose(this->transformation), normal);
	
	//normal.normalize();
	return normal;	
}

void Ellipsoid::print(){

}