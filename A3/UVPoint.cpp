#include "UVPoint.h"

UVPoint::UVPoint(){
	this->u, this->v = 0.0;
}

UVPoint::UVPoint(float u, float v){
	this->u = u;
	this->u = v;
}

float UVPoint::getU(){
	return this->u;
}

float UVPoint::getV(){
	return this->v;
}

void UVPoint::print(){
	std::cout << "(" << this->u << ", " << this->v << ")" << std::endl;
}
