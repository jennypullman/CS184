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

Curve Surface::getCurve1(){
  return this->c1;
}

Curve Surface::getCurve2(){
  return this->c2;
}

Curve Surface::getCurve3(){
  return this->c3;
}

Curve Surface::getCurve4(){
  return this->c4;
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

	if (DPdv.isDegenerate()) {
		std::cout << "V DEGENERATE - u: " << u << ", v: " << v << std::endl;

		// Curve cv1 = Curve(c1.getP1(), c2.getP1(), c3.getP1(), c4.getP1());
		// Curve cv2 = Curve(c1.getP2(), c2.getP2(), c3.getP2(), c4.getP2());
		// Curve cv3 = Curve(c1.getP3(), c2.getP3(), c3.getP3(), c4.getP3());
		// Curve cv4 = Curve(c1.getP4(), c2.getP4(), c3.getP4(), c4.getP4()); 

		// Curve 1
		// Point cpv11 = this->c1.computeDecasteljau(0);
		// Point cpv12 = this->c2.computeDecasteljau(0);
		// Point cpv13 = this->c3.computeDecasteljau(0);
		// Point cpv14 = this->c4.computeDecasteljau(0);

		// Point cpv11 = cv1.computeDecasteljau(0);
		// Point cpv12 = cv2.computeDecasteljau(0);
		// Point cpv13 = cv3.computeDecasteljau(0);
		// Point cpv14 = cv4.computeDecasteljau(0);

		// Curve cu1 = Curve(cpv11, cpv12, cpv13, cpv14);
		// Vector3 DPdu1 = cu1.computeDecNorm(u);
		Vector3 DPdu1 = c1.computeDecNorm(u);
		// DPdu1.print();

		// Curve 2
		// Point cpv21 = this->c1.computeDecasteljau(1);
		// Point cpv22 = this->c2.computeDecasteljau(1);
		// Point cpv23 = this->c3.computeDecasteljau(1);
		// Point cpv24 = this->c4.computeDecasteljau(1);

		// Point cpv21 = cv1.computeDecasteljau(1);
		// Point cpv22 = cv2.computeDecasteljau(1);
		// Point cpv23 = cv3.computeDecasteljau(1);
		// Point cpv24 = cv4.computeDecasteljau(1);

		// Curve cu2 = Curve(cpv21, cpv22, cpv23, cpv24);
		// Vector3 DPdu2 = cu2.computeDecNorm(u);
		Vector3 DPdu2 = c2.computeDecNorm(u);
		// DPdu2.print();

		// return
		// Vector3::cross(DPdu1, DPdu2).print();
		// Vector3::cross(DPdu2, DPdu1).print();
		// Vector3::cross(DPdu1, DPdu2).print();
		return Vector3::cross(DPdu1, DPdu2);
	}


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

	if (DPdu.isDegenerate()) {
		// std::cout << "U DEGENERATE" << std::endl;

		// Curve 1
		Point cp11 = this->c1.computeDecasteljau(0);
		Point cp12 = this->c2.computeDecasteljau(0);
		Point cp13 = this->c3.computeDecasteljau(0);
		Point cp14 = this->c4.computeDecasteljau(0);
		// cp1.print();
		// cp2.print();
		// cp3.print();
		// cp4.print();
		Curve cv1 = Curve(cp11, cp12, cp13, cp14);
		Vector3 DPdv1 = cv1.computeDecNorm(v);


		// Curve 2
		Point cp21 = this->c1.computeDecasteljau(1);
		Point cp22 = this->c2.computeDecasteljau(1);
		Point cp23 = this->c3.computeDecasteljau(1);
		Point cp24 = this->c4.computeDecasteljau(1);
		// cp1.print();
		// cp2.print();
		// cp3.print();
		// cp4.print();
		Curve cv2 = Curve(cp21, cp22, cp23, cp24);
		Vector3 DPdv2 = cv2.computeDecNorm(v);

		// return
		return Vector3::cross(DPdv2, DPdv1);
	}

	return Vector3::cross(DPdu, DPdv);
}

Vector3 Surface::computeNormal(Point p1, Point p2, Point p3, Point p4) {
	if (!p1.equals(p2)) {
		if (!p1.equals(p4)) {
			Vector3 v21 = Vector3(p2.getX()-p1.getX(), p2.getY()-p1.getY(), p2.getZ()-p1.getZ());
			Vector3 v41 = Vector3(p4.getX()-p1.getX(), p4.getY()-p1.getY(), p4.getZ()-p1.getZ());
			// Vector3 toReturn = Vector3::cross(v21, v41);
			// if (!toReturn.getX() || !toReturn.getY() || !toReturn.getZ()) {
			// 	std::cout << "CASE 1: " << std::endl;
			// 	toReturn.print();
			// 	v21.print();
			// 	v41.print();
			// }
			return Vector3::cross(v21, v41);
		} else {
			// std::cout << "p1 equals p4" << std::endl;
			Vector3 v21 = Vector3(p2.getX()-p1.getX(), p2.getY()-p1.getY(), p2.getZ()-p1.getZ());
			Vector3 v31 = Vector3(p3.getX()-p1.getX(), p3.getY()-p1.getY(), p3.getZ()-p1.getZ());
			// Vector3 toReturn = Vector3::cross(v21, v31);
			// if (!toReturn.getX() || !toReturn.getY() || !toReturn.getZ()) {
			// 	std::cout << "CASE 2: " << std::endl;
			// 	toReturn.print();
			// 	v21.print();
			// 	v31.print();
			// }
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
		// std::cout << "p1 equals p2" << std::endl;
		Vector3 v14 = Vector3(p1.getX()-p4.getX(), p1.getY()-p4.getY(), p1.getZ()-p4.getZ());
		Vector3 v34 = Vector3(p3.getX()-p4.getX(), p3.getY()-p4.getY(), p3.getZ()-p4.getZ());
		// Vector3 toReturn = Vector3::cross(v14, v34);
		// if (!toReturn.getX() || !toReturn.getY() || !toReturn.getZ()) {
		// 	std::cout << "CASE 3: " << std::endl;
		// 	toReturn.print();
		// 	v14.print();
		// 	v34.print();
		// }
		return Vector3::cross(v14, v34);
	}
}

Patch Surface::determinePatch(float u, float v, float du, float dv){
	float ep = 0.0001;
	//return patch starting from u,v, and going clockwise
	// if (u < 0 || v < 0 || du < 0 || dv < 0 || (u+du) > (1+ep) || (v+dv) > (1+ep)){
	// 	// cout << (u < 0) << (v < 0) << (du < 0) << (dv < 0) << (u+du >= 1) << (v+dv >= 1) << endl;
	// 	// cout << "v+dv: " << v+dv << endl;
	// 	cout << "Incorrect arguments in determinePatch\n";
	// 	//TO DO 
	// }
	// cout << "(u,v,du,dv): (" << u << ", " << v << ", " << du << ", " << dv << ")\n"; 
	Point p1 = this->computeBezier(u,v);
	// p1.print();
	Point p2 = this->computeBezier(u+du,v);
	// p2.print();
	Point p3 = this->computeBezier(u+du,v+dv);
	// p3.print();
	Point p4 = this->computeBezier(u,v+dv);
	// p4.print();
	Vector3 sn1 = this->computeNormal(u,v);
	Vector3 sn2 = this->computeNormal(u+du,v);
	Vector3 sn3 = this->computeNormal(u+du,v+dv);
	Vector3 sn4 = this->computeNormal(u,v+dv);

	Vector3 fn1 = this->computeNormal(p1, p2, p3, p4);
	Vector3 fn2 = this->computeNormal(p1, p2, p3, p4);
	Vector3 fn3 = this->computeNormal(p1, p2, p3, p4);
	Vector3 fn4 = this->computeNormal(p1, p2, p3, p4);
	return Patch(p1, p2, p3, p4, sn1, sn2, sn3, sn4, fn1, fn2, fn3, fn4);
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
