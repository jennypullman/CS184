#include <iostream>
#include <math.h>


#define PI 3.14159265  // Should be used from mathlib
inline float sqr(float x) { return x*x; }

#include <stdlib.h>

// #include "Color.h";
// #include "Triangle.h";
// #include "Sphere.h";
// #include "Ray.h";

#include "Image.h"

void runTests(){
  std::cout << "Running Test 1:  printToFile test" << std::endl;
  Image testImg = Image(10,10);
  Color testClr = Color(1.0,0.0,0.0);
  for (int i = 0; i <100; i++) {
    testImg.add_Color(i, testClr);
  }
  char fileName[] = {'t','e','s','t','I','m','g','.','p','n','g', '\0'};
  int code = testImg.printToFile(fileName);
  std::cout << "End Test 1:  code = "<< code << std::endl;
}

// Color getColorFromRay(Ray ray, float startTime){
	//find minimum time of intersection between ray and all objects
	//t>=startTime

// };


//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {
  runTests();

  std::cout << "Hello World!";
  //handle input (making objects as we go)-->keep list of objects
  //create camera, viewplane, and image object
  //for each pixel on viewplane, make ray between camera and viewplane.
  //with above ray, call our "recursive" function-->returns color
  //add color to image object
  //finally, print image

  return 0;
}








