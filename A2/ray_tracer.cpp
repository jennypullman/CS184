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
#include "Polygon.h"


struct Face {
  int vert1;
  int vert2;
  int vert3;
  int norm1;
  int norm2;
  int norm3;
};

//variables of the entire world
list<PointLight> pointLights;
list<DirectedLight> directedLights;
list<Color> ambientLights;
Material curMaterial;
Transformation curTransform;
list<Triangle> triangles;
list<Polygon> polygons;

int numFailedTests = 0;


void triangleHitTest(){
  std::cout << "Running triangleHitTest...\n";
  Vertex vert1 = Vertex(0,0,0);
  Vertex vert2 = Vertex(3,0,0);
  Vertex vert3 = Vertex(0,3,0);
  Material mat = Material(0,0,0,0,0,0,0,0,0,0,0,0,0);
  Triangle tri = Triangle(mat, vert1, vert2, vert3);
  Ray ray = Ray(1,1,-1,0,0,1);
  float hit = tri.hit(ray);
  std::cout << "Should be 1: ";
  std::cout << hit;
  std::cout << "\n";
  if (hit != 1.0){
    numFailedTests += 1;
  }
}

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
  triangleHitTest();
  std::cout << "Number of failed tests: ";
  std::cout << numFailedTests;
  std::cout << "\n";
}

Polygon readObj(string fileName){
  fstream fs;
  fs.open(fileName);
  filebuf* inbuf = fs.rdbuf();
  char c = inbuf->sbumpc();
  list<Vertex> vertices;
  list<Vector3> normals;
  list<Face> faces;
  string obj;
  string arg1;
  string arg2;
  string arg3;
  Vertex vert;
  Vector3 normal;


  while (c!=EOF){
    //get the object title
    while(c != ' ' && c!= '\n' && c != EOF){
      obj += c;
      c = inbuf->sbumpc();
    }
    //first argument
    while(c != ' ' && c != EOF && c != '\n'){
      arg1 += c;
      c = inbuf->sbumpc();
    }
    while(c == ' '){
      c = inbuf->sbumpc();
    }
    //second argument
    while(c != ' ' && c != EOF && c != '\n'){
      arg2 += c;
      c = inbuf->sbumpc();
    }
    while(c == ' '){
      c = inbuf->sbumpc();
    } 
    //third argument   
    while(c != ' ' && c != EOF && c != '\n'){
      arg3 += c;
      c = inbuf->sbumpc();
    }
    while(c == ' '){
      c = inbuf->sbumpc();
    }
    if (obj == "v"){
      vert = Vertex(stof(arg1), stof(arg2), stof(arg3));
      vertices.push_back(vert);
    } else if (obj == "vn"){
      normal = Vector3(stof(arg1), stof(arg2), stof(arg3));
      normals.push_back(normal);
    } else if (obj == "f"){
      int vertNum1, vertNum2, vertNum3;
      int normNum1, normNum2, normNum3;
      string temp = "";
      for (int i = 0; i < arg1.length(); i++){
        if (arg1[i] == '/' && temp != ""){
          vertNum1 = stoi(temp);
          temp = "";
        } else {
          temp += arg1[i];
        }
      }
      normNum1 = stoi(temp);
      temp = "";
      for (int i = 0; i < arg2.length(); i++){
        if (arg2[i] == '/' && temp != ""){
          vertNum2 = stoi(temp);
          temp = "";
        } else {
          temp += arg2[i];
        }
      }
      normNum2 = stoi(temp);
      temp = "";
      for (int i = 0; i < arg3.length(); i++){
        if (arg3[i] == '/' && temp != ""){
          vertNum3 = stoi(temp);
          temp = "";
        } else {
          temp += arg3[i];
        }
      }
      normNum3 = stoi(temp);
      temp = "";
      Face face = Face();
      face.vert1 = vertNum1;
      face.vert2 = vertNum2;
      face.vert3 = vertNum3; 
      face.norm1 = normNum1;
      face.norm2 = normNum2;
      face.norm3 = normNum3;
      faces.push_back(face);
    } else {
      std::cout << "obj file incorrectly written";
    }

    if (c == '\n' || c == EOF){
      c = inbuf->sbumpc();
    }
  }
  fs.close();
  Vertex vertexArr [vertices.size()];
  for (int i = 0; i < vertices.size(); i++){
    vertexArr[i] = vertices.front();
    vertices.pop_front();
  }
  Vector3 normalArr [normals.size()];
  for (int i = 0; i < normals.size(); i++){
    normalArr[i] = normals.front();
    normals.pop_front();
  }
  //TO DO
  //not doing anything with normals currently
  Triangle curTri;
  Triangle triangleArr [faces.size()];
  Face face;
  for (int i = 0; i < faces.size(); i++){
    face = faces.front();
    //make sure this doesn't give errors
    faces.pop_front();
    curTri = Triangle(curMaterial, vertexArr[face.vert1], vertexArr[face.vert2], vertexArr[face.vert3],
      normalArr[face.norm1], normalArr[face.norm2], normalArr[face.norm3]);    
    triangleArr[i] = curTri;
  }
  polygons.push_back(Polygon(curMaterial, triangleArr, faces.size()));
}

void handleArgs(int numArgs, float args[], string info){
  int argIndex = 0;
  string arg = "";
  int i = 0;

  while (i < info.length() && info[i] != '\n'){
    if (info[i] == ' '){
      while (info[i] == ' '){
        i++;
      };
      args[argIndex] = stof(arg);
      argIndex += 1;
      arg = "";

    } else {
      arg += info[i];
      i++;
    }
  }
  if (arg != ""){
    args[argIndex] = stof(arg);
    argIndex += 1;
  }
}

string handleStringArgs(int numArgs, string info){
  int argIndex = 0;
  string arg = "";
  int i = 0;

  while (i < info.length() && info[i] != '\n'){
    if (info[i] == ' '){
      while (info[i] == ' '){
        i++;
      };

    } else {
      arg += info[i];
      i++;
    }
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
  Vertex vert1 = Vertex(args[0], args[1], args[2]);
  Vertex vert2 = Vertex(args[3], args[4], args[5]);
  Vertex vert3 = Vertex(args[6], args[7], args[8]);
  if (!curTransform.isNull()){
    vert1 = Transformation::transformVertex(curTransform, vert1);
    vert2 = Transformation::transformVertex(curTransform, vert2);
    vert3 = Transformation::transformVertex(curTransform, vert3);
    curTransform = Transformation();
  }
  Triangle tri = Triangle(curMaterial, vert1, vert2, vert3);
  triangles.push_back(tri);
}
void handleObj(string objInfo){
  objInfo = handleStringArgs(1, objInfo);
  Polygon polygon = readObj(objInfo);
  polygons.push_back(polygon);
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
  DirectedLight light = DirectedLight(args[0], args[1], args[2], args[3], args[4], args[5]);
  directedLights.push_back(light);
}
void handleLta(string ltaInfo){
  float args[3];
  handleArgs(3, args, ltaInfo);
  Color light = Color(args[0], args[1], args[2]);
  ambientLights.push_back(light);
}
void handleMat(string matInfo){
  float args[13];
  handleArgs(13, args, matInfo);
  curMaterial = Material(args[0], args[1], args[2], args[3], args[4], args[5], args[6], 
    args[7], args[8], args[9], args[10], args[11], args[12]);
}
void handleXft(string xftInfo){
  float args[3];
  handleArgs(3, args, xftInfo);
  Transformation newTransform = Transformation(args[0], args[1], args[2], 't');
  if (curTransform.isNull()){
    curTransform = newTransform;
  } else {
    curTransform = Transformation::transformMultiply(curTransform, newTransform);
  }
}
void handleXfr(string xfrInfo){
  float args[3];
  handleArgs(3, args, xfrInfo);
  Transformation newTransform = Transformation(args[0], args[1], args[2], 'r');
  if (curTransform.isNull()){
    curTransform = newTransform;
  } else {
    curTransform = Transformation::transformMultiply(curTransform, newTransform);
  }
}
void handleXfs(string xfsInfo){
  float args[3];
  handleArgs(3, args, xfsInfo);
  Transformation newTransform = Transformation(args[0], args[1], args[2], 's');
  if (curTransform.isNull()){
    curTransform = newTransform;
  } else {
    curTransform = Transformation::transformMultiply(curTransform, newTransform);
  }
}

void handleXfz(){

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
      if (objectType == "cam"){
        handleCam(args);
      } else if (objectType == "sph"){
        handleSph(args);
      } else if (objectType == "tri"){
        handleTri(args);
      } else if (objectType == "obj"){
        handleObj(args);
      } else if (objectType == "ltp"){
        handleLtp(args);
      } else if (objectType == "ltd"){
        handleLtd(args);
      } else if (objectType == "lta"){
        handleLta(args);
      } else if (objectType == "mat"){
        handleMat(args);
      } else if (objectType == "xft"){
        handleXft(args);
      } else if (objectType == "xfr"){
        handleXfr(args);
      } else if (objectType == "xfs"){
        handleXfs(args);
      } else if (objectType == "xfz"){
        handleXfz();
      } else {
        //send warning message
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
