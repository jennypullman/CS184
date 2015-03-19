#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <list>
#include <vector>


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
#include "Ellipsoid.h"


struct Face {
  int vert1;
  int vert2;
  int vert3;
  int norm1;
  int norm2;
  int norm3;
  int numVerts;
};

//variables of the entire world
list<PointLight> pointLights;
list<DirectedLight> directedLights;
list<AmbientLight> ambientLights;
list<Light> lights;
Material curMaterial = Material();
Transformation curTransform = Transformation();
list<Triangle> triangles;
list<Polygon> polygons;
//list<Sphere> spheres;
list<Ellipsoid> ellipsoids;
list<Shape*> shapes;
int pixelsV = 1000; // Default value, TODO allow to be overridden by arguments
int pixelsH = 1000; // Default value, TODO allow to be overridden by arguments
// int pixelsV = 5; // Default value, TODO allow to be overridden by arguments
// int pixelsH = 5; // Default value, TODO allow to be overridden by arguments
ViewPlane viewplane;
Image image;
Camera camera;

int numFailedTests = 0;


void inverseTransformTest(){
  std::cout << "Running inverseTransformTest...\n";
  float matrix [16] = {1, 2, 5, 0, 1, 3, 5, 6, 2, 2, 1, 4, 0, 0, 0, 1};
  Transformation transform = Transformation(matrix);
  transform.print();
  transform = Transformation::getInverse(transform);
  std::cout << "Inverse: \n";
  transform.print();

  std::cout << "Running inverseTransformTest second time...\n";
  float matrix2 [16] = {3, 1, 6, 4, 3, 2, 8, 0, 0, 2, 1, 0, 3, 1, 9, 1};
  transform = Transformation(matrix2);
  transform.print();
  transform = Transformation::getInverse(transform);
  std::cout << "Inverse: \n";
  transform.print();

  std::cout << "Running inverseTransformTest third time...\n";
  float matrix3 [16] = {4, 5, 7, 1, 0, 3, 2, 8, 9, 1, 0, 9, 0, 1, 5, 3};
  transform = Transformation(matrix3);
  transform.print();
  transform = Transformation::getInverse(transform);
  std::cout << "Inverse: \n";
  transform.print();
}

void transformMultiplyTest(){
  std::cout << "Running transformMultiplyTest...\n";
  float matrix [16] = {1, 2, 5, 0, 1, 3, 5, 6, 2, 2, 1, 4, 0, 0, 0, 1};
  float matrix2 [16] = {3, 1, 6, 4, 3, 2, 8, 0, 0, 2, 1, 0, 3, 1, 9, 1};
  Transformation t1 = Transformation(matrix);
  Transformation t2 = Transformation(matrix2);
  Transformation transform = Transformation::transformMultiply(t1, t2);
  transform.print();
}

void triangleHitTest(){
  std::cout << "Running triangleHitTest...\n";
  Vertex vert1 = Vertex(0,0,0);
  Vertex vert2 = Vertex(3,0,0);
  Vertex vert3 = Vertex(0,3,0);
  Material mat = Material(0,0,0,0,0,0,0,0,0,0,0,0,0);
  Transformation trans = Transformation();
  Triangle tri = Triangle(mat, trans, vert1, vert2, vert3);
  Ray ray = Ray(1,1,-1,0,0,1);
  float hit = tri.hit(ray);
  std::cout << "Should be 1: ";
  std::cout << hit;
  std::cout << "\n";
  if (hit != 1.0){
    numFailedTests += 1;
  }
}

void ellipsoidHitTest(){
  std::cout << "Running ellipsoidHitTest...\n";
  Material material = Material(1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 2.0, 1.0, 1.0, 1.0);
  float transform [16] = {1.0/2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
  Transformation transformation = Transformation(transform);
  std::cout << "Transformation in ellipse test: ";
  transformation.print();
  Ellipsoid ellipsoid = Ellipsoid(material, transformation, 0, 0, 0, 3);
  Ray ray = Ray(0, 0, -1, 1, 1, 1);
  float hit = ellipsoid.hit(ray);
  std::cout << "Should be -1: ";
  std::cout << hit;
  std::cout << "\n";
  
  if (hit != 4.0) {
    numFailedTests += 1;
  }
  ray = Ray(0, 0, 5, 0, 0, -1);
  hit = ellipsoid.hit(ray);
  std::cout << "Should be 4.666667: ";
  std::cout << hit;
  std::cout << "\n";
  std::cout << "Point should be (0, 0, .333333): \n";
  std::cout << "Point: (";
  Point hitPoint = ellipsoid.getMostRecentHitPoint();
  std::cout << hitPoint.getX();
  std::cout << ", ";
  std::cout << hitPoint.getY();
  std::cout << ", ";
  std::cout << hitPoint.getZ();
  std::cout << ") \n";

  //hitting ellipsoid with light
  DirectedLight dirLight = DirectedLight(-1, -1, -1, 1.0, 1.0, 1.0);
  Vector3 view = Vector3(0, 0, -1);
  Color clr = dirLight.getShadingOnObject(material, Point(0,0,1), ellipsoid.getNormalAtPoint(Point(0,0,1)),view);
  std::cout << "Color at point: (";
  std::cout << clr.get_r();
  std::cout << ", ";
  std::cout << clr.get_g();
  std::cout << ", ";
  std::cout << clr.get_b();
  std::cout << ")\n";
  
}

void unitSphereNormalTest(){
  Ellipsoid unitSphere = Ellipsoid(Material(), Transformation(), 0, 0, 0, 1);
  float z;
  Vector3 normal;
  std::cout << "Centered at origin: \n";
  for (float x = -1; x <= 1; x+=.1){
    for (float y = -1; y <=1;  y+=.1){
      z = pow(x, 2) + pow(y, 2) - 1;
      normal = unitSphere.getNormalAtPoint(Point(x, y, z));
      if (x != normal.getX() || y != normal.getY() || z != normal.getZ()){  
        std::cout << "Fail: Normal should be (";
        std::cout << x;
        std::cout << ", ";
        std::cout << y;
        std::cout << ", ";
        std::cout << z;
        std::cout << ") but is: (";
        std::cout << normal.getX();
        std::cout << ", ";
        std::cout << normal.getY();
        std::cout << ", ";
        std::cout << normal.getZ();
        std::cout << ")\n";
      }

    }
  }

  std::cout << "Centered at (0, 0, -1)";
  unitSphere = Ellipsoid(Material(), Transformation(), 0, 0, -1, 1);
  for (float x = -1; x <= 1; x+=.1){
    for (float y = -1; y <=1;  y+=.1){
      z = pow(x, 2) + pow(y, 2) - 1;
      normal = unitSphere.getNormalAtPoint(Point(x, y, z));
      if (x != normal.getX() || y != normal.getY() || z+1 != normal.getZ()){  
        std::cout << "Fail: Normal should be (";
        std::cout << x;
        std::cout << ", ";
        std::cout << y;
        std::cout << ", ";
        std::cout << z;
        std::cout << ") but is: (";
        std::cout << normal.getX();
        std::cout << ", ";
        std::cout << normal.getY();
        std::cout << ", ";
        std::cout << normal.getZ();
        std::cout << ")\n";
      }

    }
  }

  std::cout << "Intersection Test...\n";
  Point tmpCam = Point(0, 0, 5);
  Point viewPoint = Point(0,-5.0/6,0);
  Ray viewRay = Ray(viewPoint.getX(), viewPoint.getY(), viewPoint.getZ(), 
    viewPoint.getX()-tmpCam.getX(), viewPoint.getY()-tmpCam.getY(), 
    viewPoint.getZ()-tmpCam.getZ());
  std::cout << "View ray should be: (0,-0.83333,0) + (0,-0.83333,-5)t, ray actually is:\n";
  viewRay.print();
  float hitTime = unitSphere.hit(viewRay);
  std::cout << "hitTime should be 0.135135, actually is: ";
  std::cout << hitTime;
  std::cout << "\n hitPoint should be (0, -.945945, -0.675675), actually is: (";
  std::cout << unitSphere.getMostRecentHitPoint().getX();
  std::cout << ", ";
  std::cout << unitSphere.getMostRecentHitPoint().getY();
  std::cout << ", ";
  std::cout << unitSphere.getMostRecentHitPoint().getZ();
  std::cout << ") \n";
  std::cout << "Normal from this point should be: (";
  normal = unitSphere.getNormalAtPoint(unitSphere.getMostRecentHitPoint());
  std::cout << unitSphere.getMostRecentHitPoint().getX();
  std::cout << ", ";
  std::cout << unitSphere.getMostRecentHitPoint().getY();
  std::cout << ", ";
  std::cout << unitSphere.getMostRecentHitPoint().getZ()+1;
  std::cout << ") and is: \n";  
  std::cout << normal.getX();
  std::cout << ", ";
  std::cout << normal.getY();
  std::cout << ", ";
  std::cout << normal.getZ();
  std::cout << ")\n";

}

Color pointLightShadingTest() {
  // Material mat = Material(1.0, 0.25, 0.5, 
  //   1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 2,
  //   0.0, 0.0, 0.0);

  // Point pnt = Point(0.0, 1.0, 0.0);
  // Vector3 norm = Vector3(0.0, 1.0, 0.0);

  // PointLight light = PointLight(2.0, 2.0, 2.0, 1.0, 1.0, 1.0, 0.0);

  // Color clr = light.getShadingOnObject(mat, pnt, norm, norm);

  // EXPECT R: 1.44444, G: 0.694444, B: 0.611111


  // Material mat = Material(1.0, 0.25, 0.5, 
  //   1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 2,
  //   0.0, 0.0, 0.0);

  // Point pnt = Point(0.0, 1.0, 0.0);
  // Vector3 norm = Vector3(0.0, 1.0, 0.0);

  // PointLight light = PointLight(2.0, 2.0, 2.0, 1.0, 0.0, 1.0, 0.0);

  // Color clr = light.getShadingOnObject(mat, pnt, norm, norm);

  // EXPECT R: 1.44444, G: 0, B: 0.611111


  Material mat = Material(1.0, 0.25, 0.5, 
    1.0, 1.0, 0.0, 1.0, 1.0, 0.0, 2,
    0.0, 0.0, 0.0);

  Point pnt = Point(0.0, 1.0, 0.0);
  Vector3 norm = Vector3(0.0, 1.0, 0.0);

  PointLight light = PointLight(2.0, 2.0, 2.0, 1.0, 0.0, 1.0, 0.0);

  Color clr = light.getShadingOnObject(mat, pnt, norm, norm);

  // EXPECT R: 1.44444, G: 0, B: 0.5

  return clr;
}

Color dirLightShadingTest() {
  Material mat = Material(1.0, 0.25, 0.5, 
    1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 2,
    0.0, 0.0, 0.0);

  Point pnt = Point(0.0, 1.0, 0.0);
  Vector3 norm = Vector3(0.0, 1.0, 0.0);

  DirectedLight light = DirectedLight(-2.0, -2.0, -2.0, 1.0, 1.0, 1.0);

  Color clr = light.getShadingOnObject(mat, pnt, norm, norm);

  // EXPECT R: 1.91068, G: 1.16068, B: 0.833333


  // Material mat = Material(1.0, 0.25, 0.5, 
  //   1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 2,
  //   0.0, 0.0, 0.0);

  // Point pnt = Point(0.0, 1.0, 0.0);
  // Vector3 norm = Vector3(0.0, 1.0, 0.0);

  // DirectedLight light = DirectedLight(-2.0, -2.0, -2.0, 1.0, 0.0, 1.0);

  // Color clr = light.getShadingOnObject(mat, pnt, norm, norm);

  // EXPECT R: 1.91068, G: 0, B: 0.833333


  // Material mat = Material(1.0, 0.25, 0.5, 
  //   1.0, 1.0, 0.0, 1.0, 1.0, 0.0, 2,
  //   0.0, 0.0, 0.0);

  // Point pnt = Point(0.0, 1.0, 0.0);
  // Vector3 norm = Vector3(0.0, 1.0, 0.0);

  // DirectedLight light = DirectedLight(-2.0, -2.0, -2.0, 1.0, 0.0, 1.0);

  // Color clr = light.getShadingOnObject(mat, pnt, norm, norm);

  // EXPECT R: 1.91068, G: 0, B: 0.5

  return clr;
}

Color ambLightShadingTest() {
  // Material mat = Material(1.0, 0.25, 0.5, 
  //   1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 2,
  //   0.0, 0.0, 0.0);

  // Point pnt = Point(0.0, 1.0, 0.0);
  // Vector3 norm = Vector3(0.0, 1.0, 0.0);

  // AmbientLight light = AmbientLight(1.0, 1.0, 1.0);

  // Color clr = light.getShadingOnObject(mat, pnt, norm, norm);

  // EXPECT R: 1, G: 0.25, B: 0.5


  Material mat = Material(1.0, 0.25, 0.5, 
    1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 2,
    0.0, 0.0, 0.0);

  Point pnt = Point(0.0, 1.0, 0.0);
  Vector3 norm = Vector3(0.0, 1.0, 0.0);

  AmbientLight light = AmbientLight(0.0, 1.0, 0.5);

  Color clr = light.getShadingOnObject(mat, pnt, norm, norm);

  // EXPECT R: 0, G: 0.25, B: 0.25

  return clr;
}

int printToFileTest() {
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

  return code;
}

Vector3 triangleNormTest() {
  // Triangle tri = Triangle(Material(), Vertex(0.0, 1.0, 2.0), Vertex(1.0, 2.0, 3.0), Vertex(0.25, 0.5, 0.75));
  // EXPECT X: -0.75, Y: 1.5, Z: -0.75

  Triangle tri = Triangle(Material(), Transformation(), Vertex(0.0, 1.0, 2.0), Vertex(1.0, 2.0, 3.0), Vertex(0.25, 0.5, 0.75), Vector3(), Vector3(), Vector3());
  // EXPECT X: -0.75, Y: 1.5, Z: -0.75
  Vector3 view = Vector3(0,0,1);

  return tri.getNormalAtPoint(Point(), view);

}

void runTests(){
  std::cout << "Running Test 1:  printToFile test" << std::endl;
  int code = printToFileTest();
  std::cout << "End Test 1:  code = "<< code << std::endl << std::endl;
  
  std::cout << "Running Test 2:  Triangle Hit test" << std::endl;
  triangleHitTest();
  std::cout << "End Test 2:  Number of failed tests: " << numFailedTests << "\n" << std::endl;

  std::cout << "Running Test 3:  PointLight shading test" << std::endl;
  Color clr = pointLightShadingTest();
  std::cout << "End Test 3:  R: "<< clr.get_r() << ", G: " << clr.get_g() << ", B: " << clr.get_b() << std::endl << std::endl;

  std::cout << "Running Test 4:  DirectedLight shading test" << std::endl;
  clr = dirLightShadingTest();
  std::cout << "End Test 4:  R: "<< clr.get_r() << ", G: " << clr.get_g() << ", B: " << clr.get_b() << std::endl << std::endl;

  std::cout << "Running Test 5:  AmbientLight shading test" << std::endl;
  clr = ambLightShadingTest();
  std::cout << "End Test 5:  R: "<< clr.get_r() << ", G: " << clr.get_g() << ", B: " << clr.get_b() << std::endl << std::endl;

  std::cout << "Running Test 6:  Triangle Normal test" << std::endl;
  Vector3 norm = triangleNormTest();
  std::cout << "End Test 6:  X: "<< norm.getX() << ", Y: " << norm.getY() << ", Z: " << norm.getZ() << std::endl << std::endl;

  std::cout << "Running Test 7: Ellipsoid Hit Test: " << std::endl;
  ellipsoidHitTest();
  std::cout << "End Test 7: Number of failed tests: " << numFailedTests << "\n" << std::endl;

  std::cout << "Running Test 8: Inverse Transform Test: " << std::endl;
  inverseTransformTest();
  std::cout << "End Test 8: " << "\n" << std::endl;

  std::cout << "Running Test 9: Transform Multiply Test: " << std::endl;
  transformMultiplyTest();
  std::cout << "End Test 9: " << "\n" << std::endl;

  std::cout << "Running Test 10: Unit Sphere Normal Test: " << std::endl;
  unitSphereNormalTest();
  std::cout << "End Test 10: " << std::endl << std::endl;

}


/*
 * readObj takes in a .obj fileName and parses the file.
 * It creates a polygon structure from the file and returns 
 * the polygon.
 */
Polygon readObj(string fileName){
  fstream fs;
  fs.open(fileName);
  if (!fs.is_open()){
    std::cout << "not valid file name \n";
  };
  filebuf* inbuf = fs.rdbuf();
  char c = inbuf->sbumpc();
  list<Vertex> vertices;
  list<Vector3> normals;
  list<Face> faces;
  string obj;
  Vertex vert;
  Vector3 normal;

  while (c!=EOF){
    //get the object title
    while(c != ' ' && c!= '\n' && c != EOF){
      obj += c;
      c = inbuf->sbumpc();
    }

    /***************************************************/
    /* Parsing arguments for vector and vector normals */
    /***************************************************/    
    if (obj == "v" || obj == "vn"){
      string lastChar = " ";
      int numIndex = 0;
      float nums[3];
      string arg;
      while (c != EOF && c != '\n'){
        if (c == ' ') {
          if (lastChar != " "){
            nums[numIndex] = stof(arg);
            numIndex++;
            arg = "";
          }
        } else {
          arg += c;
        }
        lastChar = c;
        c = inbuf->sbumpc();
      }
      if (arg != ""){
        nums[numIndex] = stof(arg);
        numIndex++;
      }
      
      if (obj == "v"){
        vert = Vertex(nums[0], nums[1], nums[2]);
        vertices.push_back(vert);
      } else if (obj == "vn"){
        normal = Vector3(nums[0], nums[1], nums[2]);
        normals.push_back(normal);
      }
    } 
    /*******************************/
    /* Parsing arguments for faces */
    /*******************************/ 
    else if (obj == "f"){
      string temp = "";
      int nums[6];
      string arg = "";
      int numIndex = 0;
      string lastChar = " ";
      bool hasNormals = false;
      while (c != EOF && c != '\n'){
        if (c == ' ' || c == '/'){
          if (lastChar != "/" && lastChar != " "){
            nums[numIndex] = stoi(arg);
            numIndex++;
            arg = "";
          }
        } else {
          arg += c;
        };
        lastChar = c;
        c = inbuf->sbumpc();
      };
      if (arg != ""){
        nums[numIndex] = stoi(arg);
          numIndex++;
        }
      if (numIndex < 6){
        std::cout << "should be here \n";
        Face face = Face();
        face.vert1 = nums[0];
        std::cout << nums[0];
        face.vert2 = nums[1];
        std::cout << ", ";
        std::cout << nums[1];
        face.vert3 = nums[2];
        std::cout << ", ";
        std::cout << nums[2];
        std::cout << "\n";
        face.numVerts = numIndex;
        faces.push_back(face);
      } else {
        Face face = Face();
        face.vert1 = nums[0];
        face.vert2 = nums[2];
        face.vert3 = nums[4];
        face.norm1 = nums[1];
        face.norm2 = nums[3];
        face.norm3 = nums[5];
        face.numVerts = numIndex;
        faces.push_back(face);
      }
    }
     //else {
      //std::cout << "obj file incorrectly written";
    //};

    if (c == '\n' || c == EOF || c == ' '){
      c = inbuf->sbumpc();
    };
    obj = "";
  };
  fs.close();
  /***********************************************/
  /* Putting vertex and normal lists into arrays */
  /***********************************************/

  int vertSize = vertices.size();
  vector<Vertex> vertexArr (vertSize);
  // Vertex vertexArr [vertSize];
  std::cout << "curtransform: ";
  curTransform.print();
  for (int i = 0; i < vertSize; i++){
    vertexArr[i] = Transformation::transformVertex(curTransform, vertices.front());
    //vertexArr[i] = vertices.front();
    vertices.pop_front();
  };
  int normalSize = normals.size();
  vector<Vector3> normalArr (normalSize);
  // Vector3 normalArr [normalSize];
  for (int i = 0; i < normalSize; i++){
    normalArr[i] = normals.front();
    normals.pop_front();
  };
  //TO DO
  //not doing anything with normals currently
  /*************************************************/
  /* Create trianles (and place them in a polygon) */
  /*************************************************/
  Triangle curTri;
  int numFaces = faces.size();
  vector<Triangle> triangleArr (numFaces);
  // Triangle triangleArr [numFaces];

  Face face;
  for (int i = 0; i < numFaces; i++){
    face = faces.front();
    //make sure this doesn't give errors
    faces.pop_front();
    if (face.numVerts < 6){
      curTri = Triangle(curMaterial, curTransform, vertexArr[face.vert1-1], vertexArr[face.vert2-1], vertexArr[face.vert3-1]);   
      curTri.print();
    } else {
      curTri = Triangle(curMaterial, curTransform, vertexArr[face.vert1-1], vertexArr[face.vert2-1], vertexArr[face.vert3-1],
        normalArr[face.norm1-1], normalArr[face.norm2-1], normalArr[face.norm3-1]);
    }    
    triangleArr[i] = curTri;
  };

  return Polygon(curMaterial, triangleArr.data(), numFaces);
  // return Polygon(curMaterial, triangleArr, numFaces);
}


/*
 * handleArgs takes in the number of args that there should be, 
 * parses info in order to retrieve the arguments, and returns 
 * the argumets by writing to args[].
 */
void handleArgs(int numArgs, float args[], string info){
  int argIndex = 0;
  string arg = "";
  int i = 0;

  while (i < info.length() && info[i] != '\n'){
    if (isspace(info[i])){
      while (isspace(info[i])){
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

/* 
 * handleStringArgs basically just strips info of whitespace and
 * returns the stripped string.
 */
string handleStringArgs(string info){
  int argIndex = 0;
  string arg = "";
  int i = 0;

  while (i < info.length() && info[i] != '\n'){
    if (info[i] != ' '){
      arg += info[i];
    };
    i++;
  }
  return arg;
}

/* 
 * handleCam creates a camera and image object.
 */
void handleCam(string camInfo){
  float ex, ey, ez, llx, lly, llz, lrx, lry, lrz, ulx, uly, ulz, urx, ury, urz;
  float args[15];
  handleArgs(15, args, camInfo);
  // DONE Lauren (image and viewplane)
  std::cout << camInfo;
  ex = args[0], ey = args[1], ez = args[2];
  llx = args[3], lly = args[4], llz = args[5];
  lrx = args[6], lry = args[7], lrz = args[8];
  ulx = args[9], uly = args[10], ulz = args[11];
  urx = args[12], ury = args[13], urz = args[14];

  // std::cout << "llx: " << llx << ", lly: " << lly << ", llz: " << llz << std::endl;
  // std::cout << "lrx: " << lrx << ", lry: " << lry << ", lrz: " << lrz << std::endl;
  // std::cout << "ulx: " << ulx << ", uly: " << uly << ", ulz: " << ulz << std::endl;
  // std::cout << "urx: " << urx << ", ury: " << ury << ", urz: " << urz << std::endl;

  camera = Camera(args[0], args[1], args[2]);
  image = Image(pixelsV, pixelsH);
  viewplane = ViewPlane(llx, lly, llz, lrx, lry, lrz, ulx, uly, ulz, urx, ury, urz, pixelsH, pixelsV);
}

/*
 * handleSph creates a sphere, applies the current transform, 
 * and adds it to spheres.
 */
 //TO DO transform
void handleSph(string sphInfo){
  float args[4];
  handleArgs(4, args, sphInfo);
  Vertex center = Vertex(args[0], args[1], args[2]);
  //center = Transformation::transformVertex(curTransform, center);
  //Sphere sphere = Sphere(curMaterial, center.getX(), center.getY(), center.getZ(), args[3]);
  //spheres.push_back(sphere);
  //shapes.push_back(&sphere);
  //center = Transformation::transformVertex(curTransform, center);
  Ellipsoid ellipsoid = Ellipsoid(curMaterial, curTransform, args[0], args[1], args[2], args[3]);
  ellipsoids.push_back(ellipsoid);
  shapes.push_back(&ellipsoid);
}

/*
 * handleTri creates a triangle, applies the current transform, 
 * and adds it to triangles.
 */
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
  }
  Triangle tri = Triangle(curMaterial, curTransform, vert1, vert2, vert3);
  triangles.push_back(tri);
  shapes.push_back(&tri);
}

/*
 * handleObj takes in a .obj filename (contained in objInfo). The
 * object file is parsed, and a polygon is created.
 */
void handleObj(string objInfo){
  string arg = handleStringArgs(objInfo);
  std::cout << arg;
  std::cout << "\n";
  Polygon polygon = readObj(arg);
  polygons.push_back(polygon);
  shapes.push_back(&polygon);
  //polygon.print();
}

/*
 * handleLtp creates a point light source and pushes it onto the 
 * list of point light sources. Default falloff value (args[6]), 
 * should be 0.0. 
 */
void handleLtp(string ltpInfo){
  float args[7];
  handleArgs(7, args, ltpInfo);
  PointLight light = PointLight(args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
  pointLights.push_back(light);
  lights.push_back(light);
}

/*
 * handleLtd creates a directional light source and pushes it onto the
 * list of directional light sources.
 */
void handleLtd(string ltdInfo){
  float args[6];
  handleArgs(6, args, ltdInfo);

  DirectedLight light = DirectedLight(args[0], args[1], args[2], args[3], args[4], args[5]);
  directedLights.push_back(light);
  lights.push_back(light);
}

/*
 * handleLta creates an ambient light source and pushes it oto the 
 * list of ambient light sources.
 */
 //TO DO should actually only be one ambient light source
void handleLta(string ltaInfo){
  float args[3];
  handleArgs(3, args, ltaInfo);
  AmbientLight light = AmbientLight(args[0], args[1], args[2]);
  ambientLights.push_back(light);
  lights.push_back(light);
}

/*
 * handleMat creates a material and sets curMaterial equal to it (so that
 * all proceeding objects will have that material value).
 */
void handleMat(string matInfo){
  float args[13];
  handleArgs(13, args, matInfo);
  curMaterial = Material(args[0], args[1], args[2], args[3], args[4], args[5], args[6], 
    args[7], args[8], args[9], args[10], args[11], args[12]);
}

/*
 * handleXft multiplies the current transform by the transform specified 
 * by xftInfo.
 */
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

/*
 * handleXfr multiplies the current transform by the transform specified 
 * by xfrInfo.
 */
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

/*
 * handleXfs multiplies the current transform by the transform specified 
 * by xfsInfo.
 */
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

/*
 * handleXfz resets the current transform (sets current transform equal 
 * to the identity matrix).
 */
void handleXfz(){
  //reset curTransform
  curTransform = Transformation();
}

// Color getColorFromRay(Ray ray, float startTime){
	//find minimum time of intersection between ray and all objects
	//t>=startTime

// };

/*
 * processArgs takes in the arguments from the command line and parses 
 * them. The argument should be a text file, which is then parsed to 
 * determine the different objects (camera, sphere, etc.). Then, those
 * arguments are handled by their own repective functions (e.g. handleCam).
 */
void processArgs(int argc, char *argv[]) {
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
      while (!isspace(c) && c != EOF) {
        objectType += c;
        c = inbuf->sbumpc();
      };
      if (isspace(c) && c != EOF) {
        //get rid of whitespace
        while (isspace(c) && c != EOF && c != '\n' && c != '\r'){
          c = inbuf->sbumpc();
        }

        while (c != '\n' && c != '\r' && c != EOF){
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
        //TO DO
        //send warning message
      }
      args = "";
      objectType = "";
      while (isspace(c)){
        c = inbuf->sbumpc();
      }
    }
    fs.close();
  }; 

}

Color follow_ray(Ray start_ray, int recursiveDepth){
  // Ray curr_ray = start_ray
  // initial total_dist
  // initial alpha = 1, the reflection multiplier
  // for recursion depth
    //find hit
    //update total dist (TODO double check)
    //calculate shading for hit point
    //add to clr, multiply by alpha
    //update alpha
    //determine reflecion ray (hit point in direction of reflection vector)
    //store reflection ray as curr_ray
  Ray curRay = start_ray;
  //start_ray.print();

  float totalDist = 0.0;
  float alphaR = 1.0, alphaG = 1.0, alphaB = 1.0;

  float epsilon = 0.00001; // don't want to capture ray's intersection with it's starting point

  float minHit;
  Point hitPoint;
  Triangle hitTri;
  Polygon hitPoly;
  Ellipsoid hitEllipsoid;

  Color curColor = Color();
  bool use_tri, use_poly, use_ellipsoid;

  if (shapes.size() > 0){
    for (int i = 0; i < recursiveDepth; i ++){
      // Initialize
      minHit = -1.0;
      use_tri = false, use_poly = false, use_ellipsoid = false;

      // std::cout << "\n follow i: " << i << '\n';
      //get hittime, shape, and point
      float hitTime = 0.0;
      for (Triangle triangle : triangles) { // Check all triangles
        // std::cout << "Shape type: " << typeid(triangle).name() << '\n';
        hitTime = triangle.hit(curRay);
        // std::cout << "hitTime: " << hitTime << std::endl;
        if (minHit < epsilon || (hitTime >= epsilon && hitTime < minHit)){
          minHit = hitTime;
          hitTri = triangle;
          use_tri = true;
        }
      }
      for (Polygon poly : polygons) { // Check all polygons
        // std::cout << "Shape type: " << typeid(poly).name() << '\n';
        hitTime = poly.hit(curRay);
        // std::cout << "hitTime: " << hitTime << std::endl;
        if (minHit < epsilon || (hitTime >= epsilon && hitTime < minHit)){
          minHit = hitTime;
          hitPoly = poly;
          use_tri = false;
          use_poly = true;
        }
      }
      for (Ellipsoid ellipsoid : ellipsoids) { // Check all spheres
        // std::cout << "Shape type: " << typeid(sphere).name() << '\n';
        //curRay.print();
        hitTime = ellipsoid.hit(curRay);
         //std::cout << "hitTime: " << hitTime << std::endl;

        if (minHit < epsilon || (hitTime >= epsilon && hitTime < minHit)){
          minHit = hitTime;
          hitEllipsoid = ellipsoid;
          use_tri = false;
          use_poly = false;
          use_ellipsoid = true;
        }
      }
      //std::cout << minHit;
      //std::cout << "\n";

      // std::cout << "use_tri: " << use_tri << ", use_poly: " << use_poly << ", use_ellipsoid: " << use_ellipsoid << std::endl;


      if (minHit < epsilon) {
        // std::cout<<"No real hit"<<std::endl;
        break; // No real hit
      }

      // std::cout << "minHit: " << minHit << ", hitShape: " << &hitShape << std::endl;
      Vector3 normal, view;
      Material material;
      view = Vector3(-curRay.getDirectionX(), -curRay.getDirectionY(), -curRay.getDirectionZ());
      if (use_tri){
        hitPoint = hitTri.getMostRecentHitPoint();
        normal = hitTri.getNormalAtPoint(hitPoint, view);
        material = hitTri.getMaterial();

      } else if (use_poly) {
        hitPoint = hitPoly.getMostRecentHitPoint();
        normal = hitPoly.getNormalAtPoint(hitPoint, view);
        material = hitPoly.getMaterial();
      } else if (use_ellipsoid) {
        hitPoint = hitEllipsoid.getMostRecentHitPoint();
        normal = hitEllipsoid.getNormalAtPoint(hitPoint);
        material = hitEllipsoid.getMaterial();
      }

      std::cout << "hitPoint X: " << hitPoint.getX() << ", Y: " << hitPoint.getY() << ", Z:" << hitPoint.getZ() << std::endl;
      std::cout << "normal X: " << normal.getX() << ", Y: " << normal.getY() << ", Z:" << normal.getZ() << std::endl;
      std::cout << "view X: " << view.getX() << ", Y: " << view.getY() << ", Z:" << view.getZ() << std::endl;

      //update distance
      totalDist += sqrt(pow(hitPoint.getX()-curRay.getStartX(),2)+pow(hitPoint.getY()-curRay.getStartY(),2)+
        pow(hitPoint.getZ()-curRay.getStartZ(),2));

      //get color of shape
      Color lightColor;
      float lightHitTime;
      Ray lightRay;
      Vector3 lightDir;
      for (DirectedLight light : directedLights) {
        //std::cout << "here\n";
        lightDir = light.getLightVector(hitPoint.getX(), hitPoint.getY(), hitPoint.getZ());
        if (use_tri && Vector3::dot(lightDir, hitTri.getNormalAtPoint(hitPoint, view)) < 0) { // light behind surface
          // std::cout<<"Light behind surface tri"<<std::endl;
          continue;
        }
        if (use_poly && Vector3::dot(lightDir, hitPoly.getNormalAtPoint(hitPoint, view)) < 0) { // light behind surface
          // std::cout<<"Light behind surface poly"<<std::endl;
          continue;
        }
        if (use_ellipsoid && Vector3::dot(lightDir, hitEllipsoid.getNormalAtPoint(hitPoint)) < 0) { // light behind surface
          // std::cout<<"Light behind surface ellipse"<<std::endl;
          continue;
        }

        lightRay = Ray(hitPoint.getX(), hitPoint.getY(), hitPoint.getZ(), lightDir.getX(), lightDir.getY(), lightDir.getZ());

        // COPIED CODE FROM ABOVE
        hitTime = 0.0;
        minHit = -1.0;
        for (Triangle triangle : triangles) { // Check all triangles
          // std::cout << "Shape type: " << typeid(triangle).name() << '\n';
          hitTime = triangle.hit(lightRay);
          // std::cout << "hitTime: " << hitTime << std::endl;
          if (minHit < epsilon || (hitTime >= epsilon && hitTime < minHit)){
            minHit = hitTime;
          }
        }
        for (Polygon poly : polygons) { // Check all polygons
          // std::cout << "Shape type: " << typeid(poly).name() << '\n';
          hitTime = poly.hit(lightRay);
          // std::cout << "hitTime: " << hitTime << std::endl;
          if (minHit < epsilon || (hitTime >= epsilon && hitTime < minHit)){
            minHit = hitTime;
          }
        }
        for (Ellipsoid ellipsoid : ellipsoids) { // Check all spheres
          // std::cout << "Shape type: " << typeid(sphere).name() << '\n';
          hitTime = ellipsoid.hit(lightRay);
          // std::cout << "hitTime: " << hitTime << std::endl;
          if (minHit < epsilon || (hitTime >= epsilon && hitTime < minHit)){
            minHit = hitTime;
          }
        }
        //std::cout << minHit;
        //std::cout << "\n";
        // std::cout << "hit time: " << minHit << std::endl;
        // END COPIED CODE FROM ABOVE
        if (minHit > epsilon) {
          // std::cout<<"Object between light and surface, min hit: " << minHit <<std::endl;
          // std::cout<<"Light Ray Start X: " << lightRay.getStartX() << ", Y:" << lightRay.getStartY() << ", Z: " << lightRay.getStartZ() <<std::endl;
          // std::cout<<"Light Ray Direction X: " << lightRay.getDirectionX() << ", Y:" << lightRay.getDirectionY() << ", Z: " << lightRay.getDirectionZ() <<std::endl;
          continue;
        }

        // DONE calc normal and view vectors
        lightColor = light.getShadingOnObject(material,hitPoint, normal, view);
        // std::cout << "color R: " << lightColor.get_r() << ", G: " << lightColor.get_g() << ", G:" << lightColor.get_b() << std::endl;
        // if (i==0){
          // std::cout << "alpha R: " << alphaR << ", G: " << alphaG << ", B:" << alphaB << std::endl; 
        // }
        /*std::cout << "Light Color: ";
        std::cout << lightColor.get_r();
        std::cout << ", ";
        std::cout << lightColor.get_g();
        std::cout << ", ";
        std::cout << lightColor.get_b();
        std::cout << "\n";*/
        // lightColor = light.getShadingOnObject(hitShape.getMaterial(),hitPoint, normal, view);
          /*if (lightColor.get_r() != 0 || lightColor.get_g() != 0 || lightColor.get_b() != 0){
    std::cout << "Final Color: ";
        std::cout << lightColor.get_r();
        std::cout << ", ";
        std::cout << lightColor.get_g();
        std::cout << ", ";
        std::cout << lightColor.get_b();
        std::cout << "\n";
  }*/
        curColor.update_r(curColor.get_r()+alphaR*lightColor.get_r());
        curColor.update_g(curColor.get_g()+alphaG*lightColor.get_g());
        curColor.update_b(curColor.get_b()+alphaB*lightColor.get_b());  
          /*if (curColor.get_r() != 0 || curColor.get_g() != 0 || curColor.get_b() != 0){
    std::cout << "Final Color: ";
        std::cout << curColor.get_r();
        std::cout << ", ";
        std::cout << curColor.get_g();
        std::cout << ", ";
        std::cout << curColor.get_b();
        std::cout << "\n";
  }      */
      }

      for (PointLight light : pointLights) {

        lightDir = light.getLightVector(hitPoint.getX(), hitPoint.getY(), hitPoint.getZ());
        if (use_tri && Vector3::dot(lightDir, hitTri.getNormalAtPoint(hitPoint, view)) < 0) { // light behind surface
          // std::cout<<"Light behind surface tri"<<std::endl;
          continue;
        }
        if (use_poly && Vector3::dot(lightDir, hitPoly.getNormalAtPoint(hitPoint, view)) < 0) { // light behind surface
          // std::cout<<"Light behind surface poly"<<std::endl;
          continue;
        }
        if (use_ellipsoid && Vector3::dot(lightDir, hitEllipsoid.getNormalAtPoint(hitPoint)) < 0) { // light behind surface
          // std::cout<<"Light behind surface ellipse"<<std::endl;
          continue;
        }

        lightRay = Ray(hitPoint.getX(), hitPoint.getY(), hitPoint.getZ(), lightDir.getX(), lightDir.getY(), lightDir.getZ());

        // COPIED CODE FROM ABOVE
        hitTime = 0.0;
        minHit = -1.0;
        for (Triangle triangle : triangles) { // Check all triangles
          // std::cout << "Shape type: " << typeid(triangle).name() << '\n';
          hitTime = triangle.hit(lightRay);
          // std::cout << "hitTime: " << hitTime << std::endl;
          if (minHit < epsilon || (hitTime >= epsilon && hitTime < minHit)){
            minHit = hitTime;
          }
        }
        for (Polygon poly : polygons) { // Check all polygons
          // std::cout << "Shape type: " << typeid(poly).name() << '\n';
          hitTime = poly.hit(lightRay);
          // std::cout << "hitTime: " << hitTime << std::endl;
          if (minHit < epsilon || (hitTime >= epsilon && hitTime < minHit)){
            minHit = hitTime;
          }
        }
        for (Ellipsoid ellipsoid : ellipsoids) { // Check all spheres
          // std::cout << "Shape type: " << typeid(sphere).name() << '\n';
          hitTime = ellipsoid.hit(lightRay);
          // std::cout << "hitTime: " << hitTime << std::endl;
          if (minHit < epsilon || (hitTime >= epsilon && hitTime < minHit)){
            minHit = hitTime;
          }
        }

        // std::cout << "hit time: " << minHit << std::endl;
        // END COPIED CODE FROM ABOVE
        if (minHit > epsilon && minHit <= 1.0) {
          // std::cout << "AHHHHHHH" << std::e;ndl
          continue;
        }

        // DONE calc normal and view vectors
        lightColor = light.getShadingOnObject(material,hitPoint, normal, view);
        // std::cout << "Light: ";
        // std::cout << lightColor.get_r();
        // std::cout << ", ";
        // std::cout << lightColor.get_g();
        // std::cout << ", ";
        // std::cout << lightColor.get_b();
        // std::cout << "\n";

        // lightColor = light.getShadingOnObject(hitShape.getMaterial(),hitPoint, normal, view); 
        int falloff = light.getFalloff();
        lightColor = Color::scalar_mult(lightColor, 1.0/(pow(totalDist, falloff)));


        curColor.update_r(curColor.get_r()+alphaR*lightColor.get_r());
        curColor.update_g(curColor.get_g()+alphaG*lightColor.get_g());
        curColor.update_b(curColor.get_b()+alphaB*lightColor.get_b());        
      }

      for (AmbientLight light : ambientLights) {
        // DONE calc normal and view vectors
        lightColor = light.getShadingOnObject(material,hitPoint, normal, view);

        // lightColor = light.getShadingOnObject(hitShape.getMaterial(),hitPoint, normal, view);
        curColor.update_r(curColor.get_r()+alphaR*lightColor.get_r());
        curColor.update_g(curColor.get_g()+alphaG*lightColor.get_g());
        curColor.update_b(curColor.get_b()+alphaB*lightColor.get_b());  
          /*if (curColor.get_r() != 0 || curColor.get_g() != 0 || curColor.get_b() != 0){
    std::cout << "Final Color: ";
        std::cout << curColor.get_r();
        std::cout << ", ";
        std::cout << curColor.get_g();
        std::cout << ", ";
        std::cout << curColor.get_b();
        std::cout << "\n";
  }         */
      }
      //DONE (lauren?)-->need the reflection ray
      // get direction of reflection ray
      // Vector3 dir = Vector3::subtract(Vector3::scalarMultiply(normal, 2.0), view);
      // dir.normalize();
      // curRay = Ray(hitPoint.getX(), hitPoint.getY(), hitPoint.getZ(), dir.getX(), dir.getY(), dir.getZ());


      float tmpScalar = 2*Vector3::dot(normal, view);
      Vector3 reflect = Vector3::add(Vector3::scalarMultiply(view, -1), Vector3::scalarMultiply(normal, tmpScalar));
      reflect.normalize();
      curRay = Ray(hitPoint.getX(), hitPoint.getY(), hitPoint.getZ(), reflect.getX(), reflect.getY(), reflect.getZ());
      std::cout << "reflect X: " << reflect.getX() << ", Y: " << reflect.getY() << ", Z:" << reflect.getZ() << std::endl;


      alphaR = alphaR*material.getKrr();
      alphaG = alphaG*material.getKrg();
      alphaB = alphaB*material.getKrb();
      // TODO TO DO update alpha
      // TODO TO DO use totalDist info and falloff
    }
  }
  // if (curColor.get_r() != 0 || curColor.get_g() != 0 || curColor.get_b() != 0){
    // std::cout << "Final Color: ";
    //     std::cout << curColor.get_r();
    //     std::cout << ", ";
    //     std::cout << curColor.get_g();
    //     std::cout << ", ";
    //     std::cout << curColor.get_b();
    //     std::cout << "\n";
  // }
  // std::cout << "cur_color R: " << curColor.get_r() << ", G: " << curColor.get_g() << ", G:" << curColor.get_b() << std::endl;
  return curColor;
}

int do_ray_tracing() {
  // for each pixel
    // determine view ray
    // initialize Color object
    // call follow_ray()
    // store color in image
  // return 0 if loop finishes correctly
  int numPixels = image.getNumPixels();

  // std::cout << "START pixel loop" << std::endl;
  // std::cout << "num shapes: " << shapes.size() << std::endl;
  // std::cout << "num lights: " << lights.size() << std::endl;
  
  // std::cout << "Shape: " << typeid(shape).name() << '\n';

  for (int i = 0; i < numPixels; i++){
    std::cout << "pixelnum: " << i << ": ";

    //TO DO (lauren?)
    //get correct point through viewplane
    Point viewPoint = viewplane.getPixelCoords(i);
    // std::cout << "viewPoint X: " << viewPoint.getX() << ", Y:" << viewPoint.getY() << ", Z:" << viewPoint.getZ() << std::endl;
    
    // TODO semantics of ray definition
    Ray viewRay = Ray(viewPoint.getX(), viewPoint.getY(), viewPoint.getZ(), viewPoint.getX()-camera.getX(), viewPoint.getY()-camera.getY(), viewPoint.getZ()-camera.getZ());
    // std::cout << "viewRay X: " << viewRay.getDirectionX() << ", Y:" << viewRay.getDirectionY() << ", Z:" << viewRay.getDirectionZ() << std::endl;

    //call follow_ray with 5 as recursive depth
    Color pixelColor = follow_ray(viewRay, 1);
    // std::cout << "startColor R: " << startColor.get_r() << ", G: " << startColor.get_g() << ", G:" << startColor.get_b() << std::endl;
    
    // DONE lauren
    //add color to image object
    image.add_Color(i, pixelColor);
  }
  // std::cout << "END pixel loop" << std::endl;

  // std::cout << "START print to file" << std::endl;
  char fileName[] = {'t','e','s','t','I','m','g','.','p','n','g', '\0'};
  return image.printToFile(fileName);
}

//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {
  // std::cout << "Hello World!";
  // runTests();
  if (argc == 1){
    runTests();
  } else {

    std::cout << "START processArgs" << std::endl;
    processArgs(argc, argv);
    std::cout << "END processArgs" << std::endl;

    std::cout << "START do_ray_tracing" << std::endl;
    int success = do_ray_tracing();
    std::cout << "END do_ray_tracing: " << success << std::endl;
  }

  return 0;
}
