#include "Shape.h";
#include "Vertex.h";

class Triangle : Shape{
public:
	Triangle();
	Triangle(float r, float g, float b, Vertex *vertices);

	//instance methods
	Color getColor();
	float hit(Ray ray);

private:
	float r;
	float g;
	float b;
	Vertex *vertices;
};