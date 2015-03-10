class Ray {
public:
	Ray(float startx, float starty, float startz, float dirx, float diry, float dirz);

	//instance methods
	float getStart();
	float getDirection();

private:
	float startx, starty, startz, dirz, diry, dirz;
};