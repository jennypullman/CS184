#include <stdexcept>
#include <math.h>
class Vector3 {
	float x;
	float y;
	float z;
	Vector3(){
		this->x = 0.0;
		this->y = 0.0;
		this->z = 0.0;
	}
	Vector3(float x, float y, float z){
		this->x = x;
		this->y = y;
		this->z = z;
	}
	float getX(){
		return x;
	}
	float getY(){
		return y;
	}
	float getZ(){
		return z;
	}
	static Vector3 add(Vector3 vec1, Vector3 vec2){
		return Vector3(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
	}
	//return vec1 - vec2
	static Vector3 subtract(Vector3 vec1, Vector3 vec2){
		return Vector3(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
	}
	static float dot(Vector3 vec1, Vector3 vec2){
		return vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
	}
	//return vec1 x vec2
	static Vector3 cross(Vector3 vec1, Vector3 vec2){
		return Vector3(vec1.y*vec2.z - vec1.z*vec2.y, vec1.z*vec2.x - vec1.x*vec2.z, vec1.x*vec2.y - vec1.y*vec2.x);
	}
	static Vector3 scalarMultiply(Vector3 vec, float i){
		return Vector3(vec.x*i, vec.y*i, vec.z*i);
	}
	static Vector3 scalarDivide(Vector3 vec, float i){
		if (i != 0) {
			return Vector3(vec.x / i, vec.y / i, vec.z / i);
		}
		throw std::overflow_error("Divide by zero error.");
	}

	void normalize() {
		float magnitude = sqrt( x^2 + y^2 + z^2 );
		x = x/magnitude;
		y = y/magnitude;
		z = z/magnitude;
	}
};