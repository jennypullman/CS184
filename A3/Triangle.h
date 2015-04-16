#include "UVPoint.h"

class Triangle{

public:
	Triangle();
	Triangle(Point p1, Point p2, Point p3, UVPoint uv1, UVPoint uv2, UVPoint uv3);
	
	//instance methods
	Point getP1();
	Point getP2();
	Point getP3();
	
	UVPoint getUV1();
	UVPoint getUV2();
	UVPoint getUV3();

	Point getMidpoint12();
	Point getMidpoint23();
	Point getMidpoint31();

	UVPoint getUVMidpoint12();
	UVPoint getUVMidpoint23();
	UVPoint getUVMidpoint31();

private:
	Point p1, p2, p3;
	UVPoint uv1, uv2, uv3;
};
