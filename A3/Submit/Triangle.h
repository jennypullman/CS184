#include "UVPoint.h"
#include "Vector3.h"

class Triangle{

public:
	Triangle();
	Triangle(Point p1, Point p2, Point p3, UVPoint uv1, UVPoint uv2, UVPoint uv3, 
		 Vector3 fn, Vector3 sn1, Vector3 sn2, Vector3 sn3);
	
	//instance methods
	Point getP1();
	Point getP2();
	Point getP3();
	
	UVPoint getUV1();
	UVPoint getUV2();
	UVPoint getUV3();

	Vector3 getFN();

	Vector3 getSN1();
	Vector3 getSN2();
	Vector3 getSN3();

	Point getMidpoint12();
	Point getMidpoint23();
	Point getMidpoint31();

	UVPoint getUVMidpoint12();
	UVPoint getUVMidpoint23();
	UVPoint getUVMidpoint31();

	void printUV();
	void print();

private:
	Point p1, p2, p3;
	UVPoint uv1, uv2, uv3;
	Vector3 fn, sn1, sn2, sn3;
};
