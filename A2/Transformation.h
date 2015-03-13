#include "Vector3.h"

class Transformation {
	public:
		Transformation();
		Transformation(float f1, float f2, float f3, char type);
		Transformation(float f[]);

		//instance methods
		float* getMatrix();

		//static methods
		static Transformation transformMultiply(Transformation trans1, Transformation trans2);
		static Vector3 vectorMultiply(Transformation trans, Vector3 vec);

	private:
		float matrix[16];
};