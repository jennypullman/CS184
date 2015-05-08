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
	float thetaEpisilon = 0.000000000001;
	if (type == 't'){
		// std::cout << "translate\n";
		this->matrix[0] = 1.0;
		this->matrix[3] = f1;
		this->matrix[5] = 1.0;
		this->matrix[7] = f2;
		this->matrix[10] = 1.0;
		this->matrix[11] = f3;
		this->matrix[15] = 1.0;
	} else if (type == 'r'){
		Vector3 rhat = Vector3(f1, f2, f3);
		// std::cout << "f1 = " << f1 << "\n";
		// std::cout << "f2 = " << f2 << "\n";
		// std::cout << "f3 = " << f3 << "\n";
		float theta = rhat.getMagnitude();
		if (theta == 0.0){
			//TO DO
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
			return;
		}
		float sinTheta = sin(theta*M_PI/180);
		float cosTheta = cos(theta*M_PI/180);
		/*if ((sinTheta > 0.0 && sinTheta < thetaEpisilon) || (sinTheta < 0.0 || sinTheta > -thetaEpisilon)){
			sinTheta = 0.0;
		}
		if ((cosTheta > 0.0 && cosTheta < thetaEpisilon) || (cosTheta < 0.0 || cosTheta > -thetaEpisilon)){
			cosTheta = 0.0;
		}*/
		// std::cout << "theta = " << theta << "\n";
		rhat.normalize();
		float rhatMatr[16] = {rhat.getX()*rhat.getX(), rhat.getX()*rhat.getY(), 
			rhat.getX()*rhat.getZ(), 0.0, rhat.getX()*rhat.getY(), 
			rhat.getY()*rhat.getY(), rhat.getY()*rhat.getZ(), 0.0, 
			rhat.getX()*rhat.getZ(), rhat.getY()*rhat.getZ(), 
			rhat.getZ()*rhat.getZ(), 0.0, 0.0, 0.0, 0.0, 0.0};
		// cout << "rhat getX^2 " << rhat.getX()*rhat.getX() << "\n";
		// cout << "rhatMatr0 " << rhatMatr[0] << "\n";

		float rCrossMatr[16] = {0, -rhat.getZ(), rhat.getY(), 0.0, rhat.getZ(), 
			0.0, -rhat.getX(), 0.0, -rhat.getY(), rhat.getX(), 0.0, 0.0, 
			0.0, 0.0, 0.0, 0.0};
		Transformation rhatTransform = Transformation(rhatMatr);
		// rhatTransform.print();
		Transformation rCross = Transformation(rCrossMatr);
		// rCross.print();
		Transformation finalTransform = Transformation::scaleTransformation(rCross, sinTheta);
		// finalTransform.print();
		// std::cout << "pi " << M_PI << "\n";
		// std::cout << "sin: " << sin(theta*M_PI/180) << " cos: " << cos(theta*M_PI/180) << "\n";
		finalTransform = Transformation::addTransformation(rhatTransform, finalTransform);
		Transformation rCrossSquared = Transformation::transformMultiply(rCross, rCross);
		rCrossSquared = Transformation::scaleTransformation(rCrossSquared, -cosTheta);
		finalTransform = Transformation::addTransformation(finalTransform, rCrossSquared);

		float *finalTransformMatrix = finalTransform.getMatrix();
		this->matrix[0] = finalTransformMatrix[0];
		this->matrix[1] = finalTransformMatrix[1];
		this->matrix[2] = finalTransformMatrix[2];
		this->matrix[4] = finalTransformMatrix[4];
		this->matrix[5] = finalTransformMatrix[5];
		this->matrix[6] = finalTransformMatrix[6];
		this->matrix[8] = finalTransformMatrix[8];
		this->matrix[9] = finalTransformMatrix[9];
		this->matrix[10] = finalTransformMatrix[10];
		//print();

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

Transformation Transformation::scaleTransformation(Transformation trans, float scalar){
	float matrix[16];
	float *transMatr = trans.getMatrix();
	matrix[0] = scalar*transMatr[0];
	matrix[1] = scalar*transMatr[1];
	matrix[2] = scalar*transMatr[2];
	matrix[3] = scalar*transMatr[3];
	matrix[4] = scalar*transMatr[4];
	matrix[5] = scalar*transMatr[5];
	matrix[6] = scalar*transMatr[6];
	matrix[7] = scalar*transMatr[7];
	matrix[8] = scalar*transMatr[8];
	matrix[9] = scalar*transMatr[9];
	matrix[10] = scalar*transMatr[10];
	matrix[11] = scalar*transMatr[11];
	matrix[12] = scalar*transMatr[12];
	matrix[13] = scalar*transMatr[13];
	matrix[14] = scalar*transMatr[14];
	matrix[15] = scalar*transMatr[15];
	return Transformation(matrix);
}

Transformation Transformation::addTransformation(Transformation trans1, Transformation trans2){
	float *trans1Matr = trans1.getMatrix();
	float *trans2Matr = trans2.getMatrix();
	float newMatr[16];
	newMatr[0] = trans1Matr[0] + trans2Matr[0];
	newMatr[1] = trans1Matr[1] + trans2Matr[1];
	newMatr[2] = trans1Matr[2] + trans2Matr[2];
	newMatr[3] = trans1Matr[3] + trans2Matr[3];
	newMatr[4] = trans1Matr[4] + trans2Matr[4];
	newMatr[5] = trans1Matr[5] + trans2Matr[5];
	newMatr[6] = trans1Matr[6] + trans2Matr[6];
	newMatr[7] = trans1Matr[7] + trans2Matr[7];
	newMatr[8] = trans1Matr[8] + trans2Matr[8];
	newMatr[9] = trans1Matr[9] + trans2Matr[9];
	newMatr[10] = trans1Matr[10] + trans2Matr[10];
	newMatr[11] = trans1Matr[11] + trans2Matr[11];
	newMatr[12] = trans1Matr[12] + trans2Matr[12];
	newMatr[13] = trans1Matr[13] + trans2Matr[13];
	newMatr[14] = trans1Matr[14] + trans2Matr[14];
	newMatr[15] = trans1Matr[15] + trans2Matr[15];
	return Transformation(newMatr);
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