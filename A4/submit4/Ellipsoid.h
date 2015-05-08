#include "Polygon.h"

class Ellipsoid: public Shape{

public: 
	Ellipsoid();
	Ellipsoid(Material material, Transformation transformation, 
		float radius, float xRadius, bool isBallJoint);

	//instance methods
	Material getMaterial();
	float hit(Ray ray);
	float getCenterX();
	float getCenterY();
	float getCenterZ();
	float getOriginalRadius();
	void setLeft(Ellipsoid* jnt);
	void setRight(Ellipsoid* jnt);
	bool isJoint();
	Ellipsoid* getLeft();
	Ellipsoid* getRight();
	float getXRadius();
	void updateTransformation(Transformation trans);
	void revertTransformation();

	void setTheta(float thetaX, float thetaY, float thetaZ);
	float getThetaX();
	float getThetaY();
	float getThetaZ();

	Point getMostRecentHitPoint();
	Vector3 getNormalAtPoint(Point pnt);
	void print();

private:
	Material material;   // Material of sphere
	float cx;		// Center x
	float cy;		// Center y
	float cz;		// Center z
	float radius;
	float thetaX, thetaY, thetaZ;
	Transformation scaleTransformation;
	Transformation transformation;
	Transformation inverseTransformation;
	Point mostRecentHitPoint;
	Ellipsoid* left;
	Ellipsoid* right;
	bool isBallJoint;
	float xRadius;	
};