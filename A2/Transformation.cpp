#include "Transformation.h"

Transformation::Transformation(){
	//identity matrix
	this->matrix[0] = 1.0;
	this->matrix[1] = 0.0;
	this->matrix[2] = 0.0;
	this->matrix[3] = 0.0;
	this->matrix[4] = 0.0;
	this->matrix[5] = 1.0;
	this->matrix[6] = 0.0;
	this->matrix[7] = 0.0;
	this->matrix[8] = 0.0;
	this->matrix[9] = 0.0;
	this->matrix[10] = 1.0;
	this->matrix[11] = 0.0;
	this->matrix[12] = 0.0;
	this->matrix[13] = 0.0;
	this->matrix[14] = 0.0;
	this->matrix[15] = 1.0;
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
		std::cout << "translate\n";
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
	this->matrix[9] = f[9];
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
	for (int j = 0; j < 4; j++){
		startMat1 = j*4;
		for (int i = 0; i < 4; i++){
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

	x = matr[0]*vec.getX()+matr[1]*vec.getY()+matr[2]*vec.getZ();
	y = matr[4]*vec.getX()+matr[5]*vec.getY()+matr[6]*vec.getZ();
	z = matr[8]*vec.getX()+matr[9]*vec.getY()+matr[10]*vec.getZ();
	//d = matr[12]*vec.getX()+matr[13]*vec.getY()+matr[14]*vec.getZ();

	x = x;
	y = y;
	z = z;
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

Point Transformation::transformPoint(Transformation trans, Point point){
	float x,y,z,d;
	float *matr = trans.getMatrix();

	x = matr[0]*point.getX()+matr[1]*point.getY()+matr[2]*point.getZ()+matr[3];
	y = matr[4]*point.getX()+matr[5]*point.getY()+matr[6]*point.getZ()+matr[7];
	z = matr[8]*point.getX()+matr[9]*point.getY()+matr[10]*point.getZ()+matr[11];
	d = matr[12]*point.getX()+matr[13]*point.getY()+matr[14]*point.getZ()+matr[15];

	x = x/d;
	y = y/d;
	z = z/d;
	return Point(x, y, z);
}

Transformation Transformation::getInverse(Transformation trans){
	float *tempMatr = trans.getMatrix();
	float b11 = (tempMatr[5]*tempMatr[10]*tempMatr[15]+tempMatr[6]*tempMatr[11]*tempMatr[13]+
		tempMatr[7]*tempMatr[9]*tempMatr[14])-(tempMatr[5]*tempMatr[11]*tempMatr[14]+
		tempMatr[6]*tempMatr[9]*tempMatr[15]+tempMatr[7]*tempMatr[10]*tempMatr[13]);
	float b21 = (tempMatr[4]*tempMatr[11]*tempMatr[14]+tempMatr[6]*tempMatr[8]*tempMatr[15]+
		tempMatr[7]*tempMatr[10]*tempMatr[12])-(tempMatr[4]*tempMatr[10]*tempMatr[15]+
		tempMatr[6]*tempMatr[11]*tempMatr[12]+tempMatr[7]*tempMatr[8]*tempMatr[14]);
	float b31 = (tempMatr[4]*tempMatr[9]*tempMatr[15]+tempMatr[5]*tempMatr[11]*tempMatr[12]+
		tempMatr[7]*tempMatr[8]*tempMatr[13])-(tempMatr[4]*tempMatr[11]*tempMatr[13]+
		tempMatr[5]*tempMatr[8]*tempMatr[15]+tempMatr[7]*tempMatr[9]*tempMatr[12]);
	float b41 = (tempMatr[4]*tempMatr[10]*tempMatr[13]+tempMatr[5]*tempMatr[8]*tempMatr[14]+
		tempMatr[6]*tempMatr[9]*tempMatr[12])-(tempMatr[4]*tempMatr[9]*tempMatr[14]+
		tempMatr[5]*tempMatr[10]*tempMatr[12]+tempMatr[6]*tempMatr[8]*tempMatr[13]);
	float det = tempMatr[0]*b11 + tempMatr[1]*b21 + tempMatr[2]*b31 + tempMatr[3]*b41;
	if (det == 0){
		return Transformation();
	}
	float b12 = (tempMatr[1]*tempMatr[11]*tempMatr[14]+tempMatr[2]*tempMatr[9]*tempMatr[15]+
		tempMatr[3]*tempMatr[10]*tempMatr[13])-(tempMatr[1]*tempMatr[10]*tempMatr[15]+
		tempMatr[2]*tempMatr[11]*tempMatr[13]+tempMatr[3]*tempMatr[9]*tempMatr[14]);
	float b13 = (tempMatr[1]*tempMatr[6]*tempMatr[15]+tempMatr[2]*tempMatr[7]*tempMatr[13]+
		tempMatr[3]*tempMatr[5]*tempMatr[14])-(tempMatr[1]*tempMatr[7]*tempMatr[14]+
		tempMatr[2]*tempMatr[5]*tempMatr[15]+tempMatr[3]*tempMatr[6]*tempMatr[13]);
	float b14 = (tempMatr[1]*tempMatr[7]*tempMatr[10]+tempMatr[2]*tempMatr[5]*tempMatr[11]+
		tempMatr[3]*tempMatr[6]*tempMatr[9])-(tempMatr[1]*tempMatr[6]*tempMatr[11]+
		tempMatr[2]*tempMatr[7]*tempMatr[9]+tempMatr[3]*tempMatr[5]*tempMatr[10]);
	float b22 = (tempMatr[0]*tempMatr[10]*tempMatr[15]+tempMatr[2]*tempMatr[11]*tempMatr[12]+
		tempMatr[3]*tempMatr[8]*tempMatr[14])-(tempMatr[0]*tempMatr[11]*tempMatr[14]+
		tempMatr[2]*tempMatr[8]*tempMatr[15]+tempMatr[3]*tempMatr[10]*tempMatr[12]);
	float b23 = (tempMatr[0]*tempMatr[7]*tempMatr[14]+tempMatr[2]*tempMatr[4]*tempMatr[15]+
		tempMatr[3]*tempMatr[6]*tempMatr[12])-(tempMatr[0]*tempMatr[6]*tempMatr[15]+
		tempMatr[2]*tempMatr[7]*tempMatr[12]+tempMatr[3]*tempMatr[4]*tempMatr[14]);
	float b24 = (tempMatr[0]*tempMatr[6]*tempMatr[11]+tempMatr[2]*tempMatr[7]*tempMatr[8]+
		tempMatr[3]*tempMatr[4]*tempMatr[10])-(tempMatr[0]*tempMatr[7]*tempMatr[10]+
		tempMatr[2]*tempMatr[4]*tempMatr[11]+tempMatr[3]*tempMatr[6]*tempMatr[8]);			
	float b32 = (tempMatr[0]*tempMatr[11]*tempMatr[13]+tempMatr[1]*tempMatr[8]*tempMatr[15]+
		tempMatr[3]*tempMatr[9]*tempMatr[12])-(tempMatr[0]*tempMatr[9]*tempMatr[15]+
		tempMatr[1]*tempMatr[11]*tempMatr[12]+tempMatr[3]*tempMatr[8]*tempMatr[13]);
	float b33 = (tempMatr[0]*tempMatr[5]*tempMatr[15]+tempMatr[1]*tempMatr[7]*tempMatr[12]+
		tempMatr[3]*tempMatr[4]*tempMatr[13])-(tempMatr[0]*tempMatr[7]*tempMatr[13]+
		tempMatr[1]*tempMatr[4]*tempMatr[15]+tempMatr[3]*tempMatr[5]*tempMatr[12]);
	float b34 = (tempMatr[0]*tempMatr[7]*tempMatr[9]+tempMatr[1]*tempMatr[4]*tempMatr[11]+
		tempMatr[3]*tempMatr[5]*tempMatr[8])-(tempMatr[0]*tempMatr[5]*tempMatr[11]+
		tempMatr[1]*tempMatr[7]*tempMatr[8]+tempMatr[3]*tempMatr[4]*tempMatr[9]);
	float b42 = (tempMatr[0]*tempMatr[9]*tempMatr[14]+tempMatr[1]*tempMatr[10]*tempMatr[12]+
		tempMatr[2]*tempMatr[8]*tempMatr[13])-(tempMatr[0]*tempMatr[10]*tempMatr[13]+
		tempMatr[1]*tempMatr[8]*tempMatr[14]+tempMatr[2]*tempMatr[9]*tempMatr[12]);
	float b43 = (tempMatr[0]*tempMatr[6]*tempMatr[13]+tempMatr[1]*tempMatr[4]*tempMatr[14]+
		tempMatr[2]*tempMatr[5]*tempMatr[12])-(tempMatr[0]*tempMatr[5]*tempMatr[14]+
		tempMatr[1]*tempMatr[6]*tempMatr[12]+tempMatr[2]*tempMatr[4]*tempMatr[13]);
	float b44 = (tempMatr[0]*tempMatr[5]*tempMatr[10]+tempMatr[1]*tempMatr[6]*tempMatr[8]+
		tempMatr[2]*tempMatr[4]*tempMatr[9])-(tempMatr[0]*tempMatr[6]*tempMatr[9]+
		tempMatr[1]*tempMatr[4]*tempMatr[10]+tempMatr[2]*tempMatr[5]*tempMatr[8]);
	float transform [16] = {b11/det, b12/det, b13/det, b14/det, b21/det, 
		b22/det, b23/det, b24/det, b31/det, b32/det, b33/det, b34/det, 
		b41/det, b42/det, b43/det, b44/det};
	return Transformation(transform);
}

Transformation Transformation::getTranspose(Transformation trans){
	float transpose [16];
	float *matr = trans.getMatrix();


	transpose[0] = matr[0];
	transpose[1] = matr[4];
	transpose[2] = matr[8];
	transpose[3] = matr[12];
	transpose[4] = matr[1];
	transpose[5] = matr[5];
	transpose[6] = matr[9];
	transpose[7] = matr[13];
	transpose[8] = matr[2];
	transpose[9] = matr[6];
	transpose[10] = matr[10];
	transpose[11] = matr[14];
	transpose[12] = matr[3];
	transpose[13] = matr[7];
	transpose[14] = matr[11];
	transpose[15] = matr[15];
	return Transformation(transpose);
}

void Transformation::print(){
	std::cout << "Printing transformation: [\nFirst row: ";
	std::cout << this->matrix[0];
	std::cout << ", "; 
	std::cout << this->matrix[1];
	std::cout << ", "; 
	std::cout << this->matrix[2];
	std::cout << ", "; 
	std::cout << this->matrix[3];
	std::cout << ", "; 
	std::cout << "Second row: ";
	std::cout << this->matrix[4];
	std::cout << ", "; 
	std::cout << this->matrix[5];
	std::cout << ", "; 
	std::cout << this->matrix[6];
	std::cout << ", "; 
	std::cout << this->matrix[7];
	std::cout << ", "; 
	std::cout << "Third row: ";
	std::cout << this->matrix[8];
	std::cout << ", "; 
	std::cout << this->matrix[9];
	std::cout << ", "; 
	std::cout << this->matrix[10];
	std::cout << ", "; 
	std::cout << this->matrix[11];
	std::cout << ", "; 
	std::cout << "Fourth row: ";
	std::cout << this->matrix[12];
	std::cout << ", "; 
	std::cout << this->matrix[13];
	std::cout << ", "; 
	std::cout << this->matrix[14];
	std::cout << ", "; 
	std::cout << this->matrix[15];
	std::cout << "] \n"; 
}