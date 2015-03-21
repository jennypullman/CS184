#include "Shape.h"
#include <stdlib.h>

Shape::Shape(){

}

Material Shape::getMaterial(){
	return Material();
}

float Shape::hit(Ray ray){
	// std::cout << "shape:hit" << std::endl;
	return 0.0;
}

Point Shape::getMostRecentHitPoint(){
	
}

void Shape::print(){

}


Vector3 Shape::getNormalAtPoint(Point pnt){
	return Vector3();
}