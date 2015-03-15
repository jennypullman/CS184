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
#include "Sphere.h"


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
list<AmbientLight> ambientLights;
list<Light> lights;
Material curMaterial;
Transformation curTransform;
list<Triangle> triangles;
list<Polygon> polygons;
list<Sphere> spheres;
list<Shape> shapes;
int pixelsV = 100; // Default value, TODO allow to be overridden by arguments
int pixelsH = 100; // Default value, TODO allow to be overridden by arguments
ViewPlane viewplane;
Image image;
Camera camera;

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

  Triangle tri = Triangle(Material(), Vertex(0.0, 1.0, 2.0), Vertex(1.0, 2.0, 3.0), Vertex(0.25, 0.5, 0.75), Vector3(), Vector3(), Vector3());
  // EXPECT X: -0.75, Y: 1.5, Z: -0.75

  return tri.getNormalAtPoint(Point());

}

void runTests(){
  std::cout << "Running Test 1:  printToFile test" << std::endl;
  int code = printToFileTest();
  std::cout << "End Test 1:  code = "<< code << std::endl;
  
  std::cout << "Running Test 2:  Triangle Hit test" << std::endl;
  triangleHitTest();
  std::cout << "End Test 2:  Number of failed tests: " << numFailedTests << "\n";

  std::cout << "Running Test 3:  PointLight shading test" << std::endl;
  Color clr = pointLightShadingTest();
  std::cout << "End Test 3:  R: "<< clr.get_r() << ", G: " << clr.get_g() << ", B: " << clr.get_b() << std::endl;

  std::cout << "Running Test 4:  DirectedLight shading test" << std::endl;
  clr = dirLightShadingTest();
  std::cout << "End Test 4:  R: "<< clr.get_r() << ", G: " << clr.get_g() << ", B: " << clr.get_b() << std::endl;

  std::cout << "Running Test 5:  AmbientLight shading test" << std::endl;
  clr = ambLightShadingTest();
  std::cout << "End Test 5:  R: "<< clr.get_r() << ", G: " << clr.get_g() << ", B: " << clr.get_b() << std::endl;

  std::cout << "Running Test 6:  Triangle Normal test" << std::endl;
  Vector3 norm = triangleNormTest();
  std::cout << "End Test 6:  X: "<< norm.getX() << ", Y: " << norm.getY() << ", Z: " << norm.getZ() << std::endl;


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
      Face face = Face();
      face.vert1 = nums[0];
      face.vert2 = nums[2];
      face.vert3 = nums[4];
      face.norm1 = nums[1];
      face.norm2 = nums[3];
      face.norm3 = nums[5];
      faces.push_back(face);
    } //else {
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
  for (int i = 0; i < vertSize; i++){
    if (!curTransform.isNull()){
      vertexArr[i] = Transformation::transformVertex(curTransform, vertices.front());
    }
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
    curTri = Triangle(curMaterial, vertexArr[face.vert1-1], vertexArr[face.vert2-1], vertexArr[face.vert3-1],
      normalArr[face.norm1-1], normalArr[face.norm2-1], normalArr[face.norm3-1]);    
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
  center = Transformation::transformVertex(curTransform, center);
  Sphere sphere = Sphere(curMaterial, center.getX(), center.getY(), center.getZ(), args[3]);
  spheres.push_back(sphere);
  shapes.push_back(sphere);
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
  Triangle tri = Triangle(curMaterial, vert1, vert2, vert3);
  triangles.push_back(tri);
  shapes.push_back(tri);
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
  shapes.push_back(polygon);
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
        //TO DO
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

void follow_ray(Ray start_ray, Color clr, int recursiveDepth){
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
  float totalDist = 0.0;
  float alpha = 1.0;
  Shape curShape;
  float minHit = -1.0;
  Point hitPoint;
  Shape hitShape;
  Color curColor = clr;
  float epsilon = 0.0001; // don't want to capture ray's intersection with it's starting point
  if (shapes.size() > 0){
    for (int i = 0; i < recursiveDepth; i ++){
      //get hittime, shape, and point
      for (Shape shape : shapes) {
        float hitTime = shape.hit(curRay);
        if (minHit < epsilon || (hitTime >= 0.0 && hitTime < minHit)){
          minHit = hitTime;
          hitShape = shape;
        }
      }
      hitPoint = hitShape.getMostRecentHitPoint();

      //update distance
      totalDist += sqrt(pow(hitPoint.getX()-curRay.getStartX(),2)+pow(hitPoint.getY()-curRay.getStartY(),2)+
        pow(hitPoint.getZ()-curRay.getStartZ(),2));

      //get color of shape
      Color lightColor;
      Vector3 normal, view;
      normal = hitShape.getNormalAtPoint(hitPoint);
      view = Vector3(curRay.getDirectionX(), curRay.getDirectionY(), curRay.getDirectionZ());
      for (Light light : lights) {
        // DONE calc normal and view vectors
        lightColor = light.getShadingOnObject(hitShape.getMaterial(),hitPoint, normal, view);
        curColor.update_r(alpha*(curColor.get_r()+lightColor.get_r()));
        curColor.update_g(alpha*(curColor.get_g()+lightColor.get_g()));
        curColor.update_b(alpha*(curColor.get_b()+lightColor.get_b()));        
      }
      //DONE (lauren?)-->need the reflection ray
      Vector3 dir = Vector3::subtract(Vector3::scalarMultiply(normal, 2.0), view);
      dir.normalize();
      curRay = Ray(hitPoint.getX(), hitPoint.getY(), hitPoint.getZ(), dir.getX(), dir.getY(), dir.getZ());
    }
  }
}

int do_ray_tracing() {
  // for each pixel
    // determine view ray
    // initialize Color object
    // call follow_ray()
    // store color in image
  // return 0 if loop finishes correctly
  int numPixels = image.getNumPixels();

  std::cout << "START pixel loop" << std::endl;
  std::cout << "num shapes: " << shapes.size() << std::endl;
  for (int i = 0; i < numPixels; i++){
    //TO DO (lauren?)
    //get correct point through viewplane
    Point viewPoint = viewplane.getPixelCoords(i);
    // TODO semantics of ray definition
    Ray viewRay = Ray(viewPoint.getX(), viewPoint.getY(), viewPoint.getZ(), viewPoint.getX()-camera.getX(), viewPoint.getY()-camera.getY(), viewPoint.getZ()-camera.getZ());

    //init Color
    Color startColor = Color();

    //call follow_ray with 5 as recursive depth
    follow_ray(viewRay, startColor, 5);

    // DONE lauren
    //add color to image object
    image.add_Color(i, startColor);
  }
  std::cout << "END pixel loop" << std::endl;

  std::cout << "START print to file" << std::endl;
  char fileName[] = {'t','e','s','t','I','m','g','.','p','n','g', '\0'};
  return image.printToFile(fileName);
}

//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {
  // std::cout << "Hello World!";
  // runTests();

  std::cout << "START processArgs" << std::endl;
  processArgs(argc, argv);
  std::cout << "END processArgs" << std::endl;

  std::cout << "START do_ray_tracing" << std::endl;
  int success = do_ray_tracing();
  std::cout << "END do_ray_tracing: " << success << std::endl;

  return 0;
}
