#include "Vertex.h"

Vertex::Vertex(){

}

Vertex::Vertex(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vertex::getX(){
	return this->x;
}

float Vertex::getY(){
	return this->y;
}

float Vertex::getZ(){
	return this->z;
}