#include "Shape.h"

Shape::Shape(){

}

Material Shape::getMaterial(){
	return Material();
}
float Shape::hit(Ray ray){
	return 0.0;
}

Point Shape::getMostRecentHitPoint(){
	
}

void Shape::print(){

}