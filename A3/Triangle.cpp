#include "Triangle.h"

Triangle::Triangle(){
}

Triangle::Triangle(Point p1, Point p2, Point p3, UVPoint uv1, UVPoint uv2, UVPoint uv3){
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->uv1 = uv1;
	this->uv2 = uv2;
	this->uv3 = uv3;
}

/*
 * Gets midpoint between points 1 and 2. For testing against the actual
 * point which should be computed by first using getUVMidpoint12 and then
 * calling decasteljau's on that point.
 */ 
Point Triangle::getMidpoint12(){
  return Point(.5*this->p1.getX()+.5*this->p2.getX(), .5*this->p1.getY()+.5*this->p2.getY(), .5*this->p1.getZ()+.5*this->p2.getZ());
}

Point Triangle::getMidpoint23(){
  return Point(.5*this->p2.getX()+.5*this->p3.getX(), .5*this->p2.getY()+.5*this->p3.getY(), .5*this->p2.getZ()+.5*this->p3.getZ());
}

Point Triangle::getMidpoint31(){
  return Point(.5*this->p3.getX()+.5*this->p1.getX(), .5*this->p3.getY()+.5*this->p1.getY(), .5*this->p3.getZ()+.5*this->p1.getZ());
}

UVPoint Triangle::getUVMidpoint12(){
  return UVPoint(.5*this->uv1.getU()+.5*this->uv2.getU(), .5*this->uv1.getV()+.5*this->uv2.getV());
}

UVPoint Triangle::getUVMidpoint23(){
  return UVPoint(.5*this->uv2.getU()+.5*this->uv3.getU(), .5*this->uv2.getV()+.5*this->uv3.getV());
}

UVPoint Triangle::getUVMidpoint31(){
  return UVPoint(.5*this->uv3.getU()+.5*this->uv1.getU(), .5*this->uv3.getV()+.5*this->uv1.getV());
}
