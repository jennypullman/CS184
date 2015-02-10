class Vector3{
public:
	Vector3();
	Vector3(float x, float y, float z);
	float getX();
	float getY();
	float getZ();
	static Vector3 add(Vector3 vec1, Vector3 vec2);
	//return vec1 - vec2
	static Vector3 subtract(Vector3 vec1, Vector3 vec2);
	static float dot(Vector3 vec1, Vector3 vec2);
	//return vec1 x vec2
	static Vector3 cross(Vector3 vec1, Vector3 vec2);
	static Vector3 scalarMultiply(Vector3 vec, int i);
	static Vector3 scalarDivide(Vector3 vec, int i);
	void normalize();
private:
	float x;
	float y;
	float z;
};