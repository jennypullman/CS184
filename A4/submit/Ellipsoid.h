#include "Polygon.h"

class Ellipsoid: public Shape{

public: 
	Ellipsoid();
	Ellipsoid(Material material, Transformation transformation, 
		float cx, float cy, float cz, float radius);

	//instance methods
	Material getMaterial();
	float hit(Ray ray);
	float getCenterX();
	float getCenterY();
	float getCenterZ();
	float getOriginalRadius();
	Point getMostRecentHitPoint();
	Vector3 getNormalAtPoint(Point pnt);
	void print();

private:
	Material material;   // Material of sphere
	float cx;		// Center x
	float cy;		// Center y
	float cz;		// Center z
	float radius;
	Transformation transformation;
	Transformation inverseTransformation;
	Point mostRecentHitPoint;	
};