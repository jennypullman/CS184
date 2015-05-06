class Point{
public:
	Point();
	Point(float x, float y, float z); //Point defined by coords

	//instance methods
	float getX();
	float getY();
	float getZ();

	float distToPt(Point p);

private:
	float x;
	float y;
	float z;
};