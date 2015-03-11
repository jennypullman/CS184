class Ray {
public:
	Ray(float startx, float starty, float startz, float dirx, float diry, float dirz);

	//instance methods
	float getStartX();
	float getStartY();
	float getStartZ();

	float getDirectionX();
	float getDirectionY();
	float getDirectionZ();


private:
	float startx, starty, startz, dirx, diry, dirz;
};