#include "Transformation.h"

Transformation::Transformation(){
	this->null = true;
}

Transformation::Transformation(float f1, float f2, float f3, char type){
	this->matrix[0] = 0.0;
	this->matrix[1] = 0.0;
	this->matrix[2] = 0.0;
	this->matrix[3] = 0.0;
	this->matrix[4] = 0.0;
	this->matrix[5] = 0.0;
	this->matrix[6] = 0.0;
	this->matrix[7] = 0.0;
	this->matrix[8] = 0.0;
	this->matrix[9] = 0.0;
	this->matrix[10] = 0.0;
	this->matrix[11] = 0.0;
	this->matrix[12] = 0.0;
	this->matrix[13] = 0.0;
	this->matrix[14] = 0.0;
	this->matrix[15] = 1.0;

	if (type == 't'){
		this->matrix[0] = 1.0;
		this->matrix[3] = f1;
		this->matrix[5] = 1.0;
		this->matrix[7] = f2;
		this->matrix[10] = 1.0;
		this->matrix[11] = f3;
		this->matrix[15] = 1.0;
	} else if (type == 'r'){
		this->matrix[1] = -f3;
		this->matrix[2] = f2;
		this->matrix[4] = f3;
		this->matrix[6] = -f1;
		this->matrix[8] = -f2;
		this->matrix[9] = f1;
	} else if (type == 's'){
		this->matrix[0] = f1;
		this->matrix[5] = f2;
		this->matrix[10] = f3;
	}
	this->null = false;
}

Transformation::Transformation(float f[]){
	this->matrix[0] = f[0];
	this->matrix[1] = f[1];
	this->matrix[2] = f[2];
	this->matrix[3] = f[3];
	this->matrix[4] = f[4];
	this->matrix[5] = f[5];
	this->matrix[6] = f[6];
	this->matrix[7] = f[7];
	this->matrix[8] = f[8];
	this->matrix[8] = f[9];
	this->matrix[10] = f[10];
	this->matrix[11] = f[11];
	this->matrix[12] = f[12];
	this->matrix[13] = f[13];
	this->matrix[14] = f[14];
	this->matrix[15] = f[15];
	this->null = false;
}

float* Transformation::getMatrix(){
	return this->matrix;
}

bool Transformation::isNull(){
	return this->null;
}

Transformation Transformation::transformMultiply(Transformation trans1, Transformation trans2){
	float matrix[16];
	float *matr1 = trans1.getMatrix();
	float *matr2 = trans2.getMatrix();
	int curIndex = 0;
	int startMat1;
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			startMat1 = j*4;
			matrix[curIndex] = matr1[startMat1]*matr2[i]+matr1[startMat1+1]*matr2[i+4]+
				matr1[startMat1+2]*matr2[i+8]+matr1[startMat1+3]*matr2[i+12];
			curIndex++;
		}
	}
	return Transformation(matrix);
}

Vector3 Transformation::vectorMultiply(Transformation trans, Vector3 vec){
	float x,y,z,d;
	float *matr = trans.getMatrix();

	x = matr[0]*vec.getX()+matr[1]*vec.getY()+matr[2]*vec.getZ()+matr[3];
	y = matr[4]*vec.getX()+matr[5]*vec.getY()+matr[6]*vec.getZ()+matr[7];
	z = matr[8]*vec.getX()+matr[9]*vec.getY()+matr[10]*vec.getZ()+matr[11];
	d = matr[12]*vec.getX()+matr[13]*vec.getY()+matr[14]*vec.getZ()+matr[15];

	x = x/d;
	y = y/d;
	z = z/d;
	return Vector3(x, y, z);
}

Vertex Transformation::transformVertex(Transformation trans, Vertex vert){
	float x,y,z,d;
	float *matr = trans.getMatrix();

	x = matr[0]*vert.getX()+matr[1]*vert.getY()+matr[2]*vert.getZ()+matr[3];
	y = matr[4]*vert.getX()+matr[5]*vert.getY()+matr[6]*vert.getZ()+matr[7];
	z = matr[8]*vert.getX()+matr[9]*vert.getY()+matr[10]*vert.getZ()+matr[11];
	d = matr[12]*vert.getX()+matr[13]*vert.getY()+matr[14]*vert.getZ()+matr[15];

	x = x/d;
	y = y/d;
	z = z/d;
	return Vertex(x, y, z);
}