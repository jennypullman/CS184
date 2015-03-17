#include <iostream>

class Ray {
public:
	Ray();
	Ray(float startx, float starty, float startz, float dirx, float diry, float dirz);

	//instance methods
	float getStartX();
	float getStartY();
	float getStartZ();

	float getDirectionX();
	float getDirectionY();
	float getDirectionZ();
	void print();


private:
	float startx, starty, startz, dirx, diry, dirz;
};