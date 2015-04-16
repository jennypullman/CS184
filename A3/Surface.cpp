#include "Surface.h"

Surface::Surface(){
	c1 = c2 = c3 = c4 = Curve();
}

Surface::Surface(Curve c1, Curve c2, Curve c3, Curve c4){
	this->c1 = c1;
	this->c2 = c2;
	this->c3 = c3;
	this->c4 = c4;
}

Point Surface::computeBezier(float u, float v){
	// cout << "COMPUTE BEZIER (u,v): (" << u << ", " << v << ")\n"; 
	Point cp1 = this->c1.computeDecasteljau(u);
	Point cp2 = this->c2.computeDecasteljau(u);
	Point cp3 = this->c3.computeDecasteljau(u);
	Point cp4 = this->c4.computeDecasteljau(u);
	// cp1.print();
	// cp2.print();
	// cp3.print();
	// cp4.print();
	Curve c = Curve(cp1, cp2, cp3, cp4);
	// cout << "printing curve: \n";
	// c.print();
	// std::cout << "BEZIER RESULT: ";
	 // c.computeDecasteljau(v).print();
	// std::cout << std::endl;
	return c.computeDecasteljau(v);
}

Vector3 Surface::computeNormal(float u, float v){
	// cout << "COMPUTE BEZIER (u,v): (" << u << ", " << v << ")\n"; 
	Point cp1 = this->c1.computeDecasteljau(u);
	Point cp2 = this->c2.computeDecasteljau(u);
	Point cp3 = this->c3.computeDecasteljau(u);
	Point cp4 = this->c4.computeDecasteljau(u);
	// cp1.print();
	// cp2.print();
	// cp3.print();
	// cp4.print();
	Curve cv = Curve(cp1, cp2, cp3, cp4);
	Vector3 DPdv = cv.computeDecNorm(v);


	Curve cv1 = Curve(c1.getP1(), c2.getP1(), c3.getP1(), c4.getP1());
	Curve cv2 = Curve(c1.getP2(), c2.getP2(), c3.getP2(), c4.getP2());
	Curve cv3 = Curve(c1.getP3(), c2.getP3(), c3.getP3(), c4.getP3());
	Curve cv4 = Curve(c1.getP4(), c2.getP4(), c3.getP4(), c4.getP4()); 

	Point cpv1 = cv1.computeDecasteljau(v);
	Point cpv2 = cv2.computeDecasteljau(v);
	Point cpv3 = cv3.computeDecasteljau(v);
	Point cpv4 = cv4.computeDecasteljau(v);

	Curve cu = Curve(cpv1, cpv2, cpv3, cpv4);
	Vector3 DPdu = cu.computeDecNorm(u);
	// cout << "printing curve: \n";
	// c.print();
	// std::cout << "BEZIER RESULT: ";
	 // c.computeDecasteljau(v).print();
	// std::cout << std::endl;
	return Vector3::cross(DPdu, DPdv);
}

Vector3 Surface::computeNormal(Point p1, Point p2, Point p3, Point p4) {
	if (!p1.equals(p2)) {
		if (!p1.equals(p4)) {
			Vector3 v21 = Vector3(p2.getX()-p1.getX(), p2.getY()-p1.getY(), p2.getZ()-p1.getZ());
			Vector3 v41 = Vector3(p4.getX()-p1.getX(), p4.getY()-p1.getY(), p4.getZ()-p1.getZ());
			return Vector3::cross(v21, v41);
		} else {
			// std::cout << "p1 equals p4" << std::endl;
			Vector3 v21 = Vector3(p2.getX()-p1.getX(), p2.getY()-p1.getY(), p2.getZ()-p1.getZ());
			Vector3 v31 = Vector3(p3.getX()-p1.getX(), p3.getY()-p1.getY(), p3.getZ()-p1.getZ());
			return Vector3::cross(v21, v31);
		}
	} else {
		// if (p1.equals(p4)) {
		// 	std::cout << "p1 equals p2 and p4" << std::endl;
		// }
		// if (p3.equals(p4)) {
		// 	std::cout << "p1 equals p2 and p3 equals p4" << std::endl;
		// }
		// std::cout << "p1 equals p2" << std::endl;
		// Vector3 v31 = Vector3(p3.getX()-p1.getX(), p3.getY()-p1.getY(), p3.getZ()-p1.getZ());
		// v31.print();
		// Vector3 v41 = Vector3(p4.getX()-p1.getX(), p4.getY()-p1.getY(), p4.getZ()-p1.getZ());
		// v41.print();
		// Vector3::cross(v31, v41).print();
		// return Vector3::cross(v31, v41);
		
		Vector3 v14 = Vector3(p1.getX()-p4.getX(), p1.getY()-p4.getY(), p1.getZ()-p4.getZ());
		Vector3 v34 = Vector3(p3.getX()-p4.getX(), p3.getY()-p4.getY(), p3.getZ()-p4.getZ());
		return Vector3::cross(v14, v34);
	}
}

Patch Surface::determinePatch(float u, float v, float du, float dv){
	//return patch starting from u,v, and going clockwise
	if (u < 0 || v < 0 || du < 0 || dv < 0 || u+du > 1 || v+dv >1){
		// cout << (u < 0) << (v < 0) << (du < 0) << (dv < 0) << (u+du >= 1) << (v+dv >= 1) << endl;
		// cout << "v+dv: " << v+dv << endl;
		cout << "Incorrect arguments in determinePatch\n";
		//TO DO 
	}
	// cout << "(u,v,du,dv): (" << u << ", " << v << ", " << du << ", " << dv << ")\n"; 
	Point p1 = this->computeBezier(u,v);
	// p1.print();
	Point p2 = this->computeBezier(u+du,v);
	// p2.print();
	Point p3 = this->computeBezier(u+du,v+dv);
	// p3.print();
	Point p4 = this->computeBezier(u,v+dv);
	// p4.print();
	// Vector3 n1 = this->computeNormal(u,v);
	// Vector3 n2 = this->computeNormal(u+du,v);
	// Vector3 n3 = this->computeNormal(u+du,v+dv);
	// Vector3 n4 = this->computeNormal(u,v+dv);

	Vector3 n1 = this->computeNormal(p1, p2, p3, p4);
	Vector3 n2 = this->computeNormal(p1, p2, p3, p4);
	Vector3 n3 = this->computeNormal(p1, p2, p3, p4);
	Vector3 n4 = this->computeNormal(p1, p2, p3, p4);
	return Patch(p1, p2, p3, p4, n1, n2, n3, n4);
}

void Surface::print(){
	std::cout << "Curve 1: ";
	this->c1.print();
	std::cout << "Curve 2: ";
	this->c2.print();
	std::cout << "Curve 3: ";
	this->c3.print();
	std::cout << "Curve 4: ";
	this->c4.print();
}