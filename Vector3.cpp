#include <stdexcept>
class Vector3 {
	int x;
	int y;
	int z;
	Vector3(int x, int y, int z){
		this->x = x;
		this->y = y;
		this->z = z;
	}
	int getX(){
		return x;
	}
	int getY(){
		return y;
	}
	int getZ(){
		return z;
	}
	static Vector3 add(Vector3 vec1, Vector3 vec2){
		return Vector3(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
	}
	//return vec1 - vec2
	static Vector3 subtract(Vector3 vec1, Vector3 vec2){
		return Vector3(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
	}
	static int dot(Vector3 vec1, Vector3 vec2){
		return vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
	}
	//return vec1 x vec2
	static Vector3 cross(Vector3 vec1, Vector3 vec2){
		return Vector3(vec1.y*vec2.z - vec1.z*vec2.y, vec1.z*vec2.x - vec1.x*vec2.z, vec1.x*vec2.y - vec1.y*vec2.x);
	}
	static Vector3 scalarMultiply(Vector3 vec, int i){
		return Vector3(vec.x*i, vec.y*i, vec.z*i);
	}
	static Vector3 scalarDivide(Vector3 vec, int i){
		if (i != 0) {
			return Vector3(vec.x / i, vec.y / i, vec.z / i);
		}
		throw std::overflow_error("Divide by zero error.");
	}
};