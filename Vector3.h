#include <stdexcept>
class Vector3{
public:
	Vector3(int x, int y, int z);
	int getX();
	int getY();
	int getZ();
	static Vector3 add(static Vector3 vec1, static Vector3 vec2);
	//return vec1 - vec2
	Vector3 subtract(Vector3 vec1, Vector3 vec2);
	static int dot(Vector3 vec1, Vector3 vec2);
	//return vec1 x vec2
	Vector3 cross(Vector3 vec1, Vector3 vec2);
	Vector3 scalarMultiply(Vector3 vec, int i);
	Vector3 scalarDivide(Vector3 vec, int i);
private:
	int x;
	int y;
	int z;
};