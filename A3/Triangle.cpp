#include "Triangle.h"

Triangle::Triangle(){
}

Triangle::Triangle(Point p1, Point p2, Point p3, UVPoint uv1, UVPoint uv2, UVPoint uv3, 
		   Vector3 fn, Vector3 sn1, Vector3 sn2, Vector3 sn3){
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->uv1 = uv1;
	this->uv2 = uv2;
	this->uv3 = uv3;
	this->fn = fn;
	this->sn1 = sn1;
	this->sn2 = sn2;
	this->sn3 = sn3;
}

Point Triangle::getP1(){
  return this->p1;
}

Point Triangle::getP2(){
  return this->p2;
}

Point Triangle::getP3(){
  return this->p3;
}

UVPoint Triangle::getUV1(){
  return this->uv1;
}

UVPoint Triangle::getUV2(){
  return this->uv2;
}

UVPoint Triangle::getUV3(){
  return this->uv3;
}

Vector3 Triangle::getFN(){
  return this->fn;
}

Vector3 Triangle::getSN1(){
  return this->sn1;
}

Vector3 Triangle::getSN2(){
  return this->sn2;
}

Vector3 Triangle::getSN3(){
  return this->sn3;
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
