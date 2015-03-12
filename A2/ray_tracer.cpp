#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <list>


#define PI 3.14159265  // Should be used from mathlib
inline float sqr(float x) { return x*x; }
using namespace std;

#include <stdlib.h>

//#include "Color.h"
//#include "Image.h"

//#include "Polygon.h"
//#include "PointLight.h"
//#include "DirectedLight.h"
//#include "Sphere.h";
//#include "Ray.h";
#include "Triangle.h"

//variables of the entire world
list<PointLight> pointLights;
list<DirectedLight> directedLights;
list<Color> ambientLights;


void runTests(){
  std::cout << "Running Test 1:  printToFile test" << std::endl;
  Image testImg = Image(12,10);
  Color testR = Color(1.0,0.0,0.0);
  Color testY = Color(1.0,1.0,0.0);
  Color testG = Color(0.0,1.0,0.0);
  Color testC = Color(0.0,1.0,1.0);
  Color testB = Color(0.0,0.0,1.0);
  Color testM = Color(1.0,0.0,1.0);
  // std::cout << "Color r = "<< testClr.get_r() << std::endl;
  for (int i = 0; i <20; i++) {
    testImg.add_Color(i, testR);
  }
  for (int i = 20; i <40; i++) {
    testImg.add_Color(i, testY);
  }
  for (int i = 40; i <60; i++) {
    testImg.add_Color(i, testG);
  }
  for (int i = 60; i <80; i++) {
    testImg.add_Color(i, testC);
  }
  for (int i = 80; i <100; i++) {
    testImg.add_Color(i, testB);
  }
  for (int i = 100; i <120; i++) {
    testImg.add_Color(i, testM);
  }
  char fileName[] = {'t','e','s','t','I','m','g','.','p','n','g', '\0'};
  int code = testImg.printToFile(fileName);
  std::cout << "End Test 1:  code = "<< code << std::endl;
}

void handleArgs(int numArgs, float args[], string info){
  int argIndex = 0;
  string arg = "";
  int i = 0;

  while (i < info.length()){
    if (info[i] == ' '){
      while (info[i] == ' '){
        i++;
      };
      std::cout << arg;
      args[argIndex] = stof(arg);
      argIndex += 1;
      arg = "";

    } else {
      arg += info[i];
      i++;
    }
  }
  if (arg != ""){
    std::cout << arg;
    args[argIndex] = stof(arg);
    argIndex += 1;
  }
}

void handleCam(string camInfo){
  float ex, ey, ez, llx, lly, llz, lrx, lry, lrz, ulx, uly, ulz, urx, ury, yrz;
  float args[14];
  handleArgs(14, args, camInfo);
}
void handleSph(string sphInfo){
  float args[4];
  handleArgs(4, args, sphInfo);
}
void handleTri(string triInfo){
  float args[9];
  handleArgs(9, args, triInfo);
}
void handleObj(string objInfo){
  float args[1];
  handleArgs(1, args, objInfo);
}
void handleLtp(string ltpInfo){
  float args[7];
  handleArgs(7, args, ltpInfo);
  PointLight light = PointLight(args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
  pointLights.push_back(light);
}
void handleLtd(string ltdInfo){
  float args[6];
  handleArgs(6, args, ltdInfo);
}
void handleLta(string ltaInfo){
  float args[3];
  handleArgs(3, args, ltaInfo);
}
void handleMat(string matInfo){
  float args[13];
  handleArgs(13, args, matInfo);
}
void handleXft(string xftInfo){
  float args[3];
  handleArgs(3, args, xftInfo);
}
void handleXfr(string xfrInfo){
  float args[3];
  handleArgs(3, args, xfrInfo);
}
void handleXfs(string xfsInfo){
  float args[3];
  handleArgs(3, args, xfsInfo);
}

// Color getColorFromRay(Ray ray, float startTime){
	//find minimum time of intersection between ray and all objects
	//t>=startTime

// };
void processArgs(int argc, char *argv[]) {
  // cout << "argc: " << argc << "\n";
  // for (int i = argc - 1; i >= 0; i--) { 
  //   cout << argv[i] << "\n";
  // }
  std::cout << "Processing...\n";
  string arg;
  string objectType = "";
  string args = "";
  if (argc != 2){
    //baaad
    std::cout << "baaad\n";
  } else {
    arg = argv[1];
    fstream fs;
    fs.open(argv[1]);
    filebuf* inbuf = fs.rdbuf();
    char c = inbuf->sbumpc();
    while (c!=EOF){
      while (c != ' ' && c != '\n' && c != EOF) {
        objectType += c;
        c = inbuf->sbumpc();
      };
      if (c != '\n' && c != EOF) {
        //get rid of whitespace
        while (c == ' ' && c != EOF && c != '\n'){
          c = inbuf->sbumpc();
        }

        while (c != '\n' && c != EOF){
          args += c;
          c = inbuf->sbumpc();
        };
      };
      std::cout << objectType;
      if (objectType == "cam"){
        std::cout << "sending to cam handler\n";
        handleCam(args);
      } else if (objectType == "sph"){

      } else if (objectType == "tri"){

      } else if (objectType == "obj"){

      } else if (objectType == "ltp"){

      } else if (objectType == "ltd"){

      } else if (objectType == "lta"){

      } else if (objectType == "mat"){

      } else if (objectType == "xft"){

      } else if (objectType == "xfr"){

      } else if (objectType == "xfs"){

      }
      args = "";
      objectType = "";
      if (c == '\r' || c == '\n'){
        c = inbuf->sbumpc();
      }
    }
    fs.close();
  };
  
}

//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {
  runTests();


  std::cout << "Hello World!";
  processArgs(argc, argv);
  //handle input (making objects as we go)-->keep list of objects
  //create camera, viewplane, and image object
  //for each pixel on viewplane, make ray between camera and viewplane.
  //with above ray, call our "recursive" function-->returns color
  //add color to image object
  //finally, print image

  return 0;
}
