#include <iostream>
#include <math.h>


#define PI 3.14159265  // Should be used from mathlib
inline float sqr(float x) { return x*x; }

#include <stdlib.h>

#include "Color.h";
#include "Triangle.h";
#include "Sphere.h";
#include "Ray.h";

Color getColorFromRay(Ray ray, float startTime){
	//find minimum time of intersection between ray and all objects
	//t>=startTime

};


//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {
  std::cout << "Hello World!";
  //handle input (making objects as we go)-->keep list of objects
  //create camera, viewplane, and image object
  //for each pixel on viewplane, make ray between camera and viewplane.
  //with above ray, call our "recursive" function-->returns color
  //add color to image object
  //finally, print image

  return 0;
}








