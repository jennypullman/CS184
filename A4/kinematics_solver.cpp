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

#include "Eigen/Dense"
#include "Eigen/SVD"
//using Eigen::MatrixXd;
//using Eigen::JacobiSVD;
using namespace Eigen;



//#include <armadillo>
//using namespace arma;


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
float curXScale = 1.0;

Triangle lastTriangle;
Polygon lastPolygon;
Ellipsoid* lastEllipsoid = NULL;
Ellipsoid lastJoint;
list<Ellipsoid> ellipsoids;

int pixelsV = 1000; // Default value, TODO allow to be overridden by arguments
int pixelsH = 1000; // Default value, TODO allow to be overridden by arguments
// int pixelsV = 5; // Default value, TODO allow to be overridden by arguments
// int pixelsH = 5; // Default value, TODO allow to be overridden by arguments
ViewPlane viewplane;
Image image;
Camera camera;
bool PRINT = false;

int numFailedTests = 0;


/*
 * readObj takes in a .obj fileName and parses the file.
 * It creates a polygon structure from the file and returns 
 * the polygon.
 */
Polygon readObj(string fileName){
  fstream fs;
  fs.open(fileName);
  if (!fs.is_open()){
    fprintf(stderr, "Could not open .obj file for reading.\n");
  }
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
      char lastChar = ' ';
      bool hasNormals = false;
      while (c != EOF && c != '\n'){
        if (isspace(c) || c == '/'){
          if (lastChar != '/' && !isspace(lastChar)){
            // std::cout << arg;
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
        // std::cout << arg;
        nums[numIndex] = stoi(arg);
          numIndex++;
        }
      if (numIndex < 6){
        // std::cout << "should be here \n";
        Face face = Face();
        face.vert1 = nums[0];
        // std::cout << nums[0];
        face.vert2 = nums[1];
        // std::cout << ", ";
        // std::cout << nums[1];
        face.vert3 = nums[2];
        // std::cout << ", ";
        // std::cout << nums[2];
        // std::cout << "\n";
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
  // std::cout << "curtransform: ";
  // curTransform.print();
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
      // curTri.print();
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
      if (argIndex >= numArgs){
        fprintf(stderr, "Warning: Too many arguments for this feature.\n");
        break;
      }
      args[argIndex] = stof(arg);
      argIndex += 1;
      arg = "";

    } else {
      arg += info[i];
      i++;
    }
  }
  if (arg != ""){
    if (argIndex >= numArgs){
      fprintf(stderr, "Warning: Too many arguments for this feature.\n");
    } else {
      args[argIndex] = stof(arg);
      argIndex += 1;
    }
  }
  if (numArgs < argIndex){
    fprintf(stderr, "Warning: Not enough arguments for this feature.\n");
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
  // std::cout << camInfo;
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
void handleJnt(string jntInfo){
  float args[1];
  handleArgs(1, args, jntInfo);
  //center = Transformation::transformVertex(curTransform, center);
  //Sphere sphere = Sphere(curMaterial, center.getX(), center.getY(), center.getZ(), args[3]);
  //spheres.push_back(sphere);
  //shapes.push_back(&sphere);
  //center = Transformation::transformVertex(curTransform, center);
  //float xRadius = curXScale*(args[0]);
  Ellipsoid ellipsoid = Ellipsoid(curMaterial, curTransform, args[0], args[0], true);
  ellipsoid.setLeft(lastEllipsoid);


  ellipsoids.push_back(ellipsoid);  
  if (lastEllipsoid != NULL){
    lastEllipsoid->setRight(&(ellipsoids.back()));

  }

  lastEllipsoid = &(ellipsoids.back());
}


/*
 * handleSph creates a sphere, applies the current transform, 
 * and adds it to spheres.
 */
 //TO DO transform
void handleSph(string sphInfo){
  float args[1];
  handleArgs(1, args, sphInfo);
  //center = Transformation::transformVertex(curTransform, center);
  //Sphere sphere = Sphere(curMaterial, center.getX(), center.getY(), center.getZ(), args[3]);
  //spheres.push_back(sphere);
  //shapes.push_back(&sphere);
  //center = Transformation::transformVertex(curTransform, center);
  float xRadius = curXScale*(args[0]);
  Ellipsoid ellipsoid = Ellipsoid(curMaterial, curTransform, args[0], xRadius, false);
  ellipsoid.setLeft(lastEllipsoid);


  ellipsoids.push_back(ellipsoid);  
  if (lastEllipsoid != NULL){
    lastEllipsoid->setRight(&(ellipsoids.back()));

  }

  lastEllipsoid = &(ellipsoids.back());
  cout << "scale: " << curXScale << "\n";
  cout << "xRadius: " << lastEllipsoid->getXRadius() << "\n";
  //cout << "theta y " << ellipsoid.getThetaY();
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
  //TO DO
  //lastTriangle.setNext(tri);
  //tri.setPrev(lastTriangle);
  lastTriangle = tri;
}

/*
 * handleObj takes in a .obj filename (contained in objInfo). The
 * object file is parsed, and a polygon is created.
 */
void handleObj(string objInfo){
  string arg = handleStringArgs(objInfo);
  // std::cout << arg;
  // std::cout << "\n";
  Polygon polygon = readObj(arg);
  //TO DO
  //lastPolygon.setNext(polygon);
  //polygon.setPrev(lastPolygon);
  lastPolygon = polygon;
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
 * handleXfs multiplies the current transform by the transform specified 
 * by xfsInfo.
 */
void handleXfs(string xfsInfo){
  float args[3];
  handleArgs(3, args, xfsInfo);

  curTransform = Transformation(args[0], args[1], args[2], 's');
  curXScale = args[0];
}

void handleXfz(){
  //reset curTransform
  curXScale = 1.0;
  curTransform = Transformation();
}



MatrixXd pinv(MatrixXd A) {
  float pinvtolerance = 0.000001;
  JacobiSVD<MatrixXd> svd(A, ComputeFullU | ComputeFullV);
  VectorXd diag = svd.singularValues();
  int diagInvSize = svd.matrixU().outerSize();
  MatrixXd diagInv(svd.matrixV().outerSize(), svd.matrixU().outerSize());
  for (int j = 0; j < svd.matrixV().outerSize(); j++){
    for (int i = 0; i < svd.matrixU().outerSize(); i++){
      if (i>=diag.size()||
        (diag(i) < pinvtolerance && diag(i) > -pinvtolerance)||
        i != j){
        diagInv(j,i) = 0.0;
      } else {
        diagInv(j,i) = 1.0/diag(i);
      }
    }
  }
  
  return svd.matrixV()*(diagInv*svd.matrixU().transpose());
}

/* TODO JENNY calculate F
*/
Point calcEndPoint(MatrixXd theta) {
  // theta is a matrix with n rows and 3 columns, where n is the number of joints
  // the Point object returned holds the point the arm points to when transformed according to theta

  return Point();
}

MatrixXd calculateJacobian() {

  // get current thetas
  // std::cout << "num ellipsoids: " << ellipsoids.size() << std::endl;
  int row = ellipsoids.size()/2; // number of arm segments
  int col = 3; // rx, ry, rz
  MatrixXd theta(row, col);

  int index = 0;

  Ellipsoid* currEllipsoid = lastEllipsoid;
  while(currEllipsoid->getLeft() != NULL){
    if (!currEllipsoid->isJoint()) {
      theta(index, 0) = currEllipsoid->getThetaX();
      theta(index, 1) = currEllipsoid->getThetaY();
      theta(index, 2) = currEllipsoid->getThetaZ();
      index++;
    }
    currEllipsoid = currEllipsoid->getLeft();
  }

  float epsilon = 0.0001;
  float denom = 2*epsilon;

  MatrixXd jacob(col, row*col); // jacobian has 3 rows and 3*n columns, where n is number of ellipsoids
  // call calcEndPoint to estimate partial derivates for jacobian
  for (int r = 0; r < row; r++) {
    for (int c = 0; c < col; c++) {
      int c_index = r*col + c; // corresponding column in jacobian

      
      // peturb specific theta to be less
      theta(r,c) = theta(r,c) - epsilon;
      Point pL = calcEndPoint(theta);

      // peturb specific theta to be more
      theta(r,c) = theta(r,c) + 2*epsilon;
      Point pR = calcEndPoint(theta);

      theta(r,c) = theta(r,c) - epsilon; // return theta to initial value
      
      // look at change in end point to estimate derivate
      float derivativeX = (pR.getX()-pL.getX())/denom;
      float derivativeY = (pR.getY()-pL.getY())/denom;
      float derivativeZ = (pR.getZ()-pL.getZ())/denom;

      jacob(0, c_index) = derivativeX;
      jacob(1, c_index) = derivativeY;
      jacob(2, c_index) = derivativeZ;
    }
  }

  return jacob;
}

void calculateAngles(Point target, MatrixXd j) {

  float epsilon = 0.0001;

  // calculate inverse of jacobian
  MatrixXd jInv = pinv(j);

  // get current thetas
  // std::cout << "num ellipsoids: " << ellipsoids.size() << std::endl;
  int row = ellipsoids.size()/2; // number of arm segments
  int col = 3; // rx, ry, rz
  MatrixXd theta(row, col);

  int index = 0;

  Ellipsoid* currEllipsoid = lastEllipsoid;
  while(currEllipsoid->getLeft() != NULL){
    if (!currEllipsoid->isJoint()) {
      theta(index, 0) = currEllipsoid->getThetaX();
      theta(index, 1) = currEllipsoid->getThetaY();
      theta(index, 2) = currEllipsoid->getThetaZ();
      index++;
    }
    currEllipsoid = currEllipsoid->getLeft();
  }

  // use iterative algorithm from piazza to update thetas - newton's method doesn't seem to work with exp. maps
  // 1. Initialize all rotations ri=0. 
  // TODO make sure it is okay to skip this

  // 2. Find the system end effector pe. Check if ||pe−g||<ϵ. If yes, we are done. Else continue to step 3.
  // int iter = 0;
  // int iterMax = 100;

  // Point endEffector;
  // while(iter < iterMax){
  //   endEffector = calcEndPoint(theta);
  //   if (target.distToPt(endEffector) < epsilon) {
  //     updateAngles(theta);
  //     return;
  //   }

  //   // update
    
  // } 



  // 3. Find the system Jacobian (discussed below) J and its pseudo inverse J+.
  // 4. Find the change in rotation dr=J+×λ(g−pe) for some positive step size λ.
  // 5. Update all rotations ri using dr. Find pi and render the system in OpenGL. Go to step 2.

}

/*
* updateTransformations creates rotation transformations 
* out of the thetas stored in each ellipsoid. That is, the 
* ellipsoids should already have the updated thetas stored in them. 
* This method just stores the final transformation for each 
* ellipsoid in the ellipsoid, so that draw will be able to see the 
* transformation.
*/
void updateTranformations(){
  if (lastEllipsoid->getLeft() != NULL){
    cout << "radii: " << lastEllipsoid->getXRadius() << " " << lastEllipsoid->getLeft()->getXRadius() << "\n";
  }
  cout << "num ellipses: " << ellipsoids.size() << "\n";

  Ellipsoid* currEllipsoid = lastEllipsoid;
  
  if (currEllipsoid == NULL){
    return;
  }
  currEllipsoid->revertTransformation();
  while(currEllipsoid->getLeft() != NULL){
    currEllipsoid = currEllipsoid->getLeft();
    currEllipsoid->revertTransformation();
  }


  Transformation totalTransform = Transformation(currEllipsoid->getXRadius(), 0.0, 0.0, 't');

  currEllipsoid = currEllipsoid->getRight();

  Transformation tmpTransform;
  while(currEllipsoid != NULL){
    tmpTransform = totalTransform;

    Transformation rotation = Transformation(currEllipsoid->getThetaX(), 
      currEllipsoid->getThetaY(), currEllipsoid->getThetaZ(), 'r');

    Transformation translate = Transformation(currEllipsoid->getXRadius(), 0.0, 0.0, 't');
    totalTransform = Transformation::transformMultiply(totalTransform, rotation);
    totalTransform = Transformation::transformMultiply(totalTransform, translate);
    currEllipsoid->updateTransformation(totalTransform);
    totalTransform.print();
    cout << "translate\n";
    if (currEllipsoid->getRight() != NULL){
      if (!currEllipsoid->getRight()->isJoint()){
        cout << "HOLY CRAP WE HAVE A PROBLEM. NO JOINT TO THE SEGMENT\n";
      }
      translate = Transformation(currEllipsoid->getXRadius()*2+currEllipsoid->getRight()->getXRadius(), 
        0.0, 0.0, 't');
      tmpTransform = Transformation::transformMultiply(tmpTransform, rotation);
      tmpTransform = Transformation::transformMultiply(tmpTransform, translate);
      currEllipsoid = currEllipsoid->getRight();
      currEllipsoid->updateTransformation(tmpTransform);

    }
    translate = Transformation(currEllipsoid->getXRadius(), 0.0, 0.0, 't');
    totalTransform = Transformation::transformMultiply(tmpTransform, translate);
    currEllipsoid = currEllipsoid->getRight();
  }
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
      Ellipsoid my;
      if (objectType == "cam"){
        handleCam(args);
      } else if (objectType == "sph"){
        cout << "heeeere\n";
        handleSph(args);
        //my = *lastEllipsoid;
        //cout << "mine\n";
        
      } else if (objectType == "jnt"){
        handleJnt(args);
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
      } else if (objectType == "xfs"){
        handleXfs(args);
      } else if (objectType == "xfz"){
        handleXfz();
      } else {
        //TO DO
        //send warning message
        fprintf(stderr, "Warning: Feature is not supported.\n");
      }
      args = "";
      objectType = "";
      while (isspace(c)){
        c = inbuf->sbumpc();
      }
    }
    fs.close();
  }; 
  

  updateTranformations();
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
  // std::cout << PRINT << std::endl;


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

  //TO DO
  if (ellipsoids.size() > 0){
    for (int i = 0; i < recursiveDepth; i ++){
      // Initialize
      minHit = -1.0;
      use_tri = false, use_poly = false, use_ellipsoid = false;

      // std::cout << "\n follow i: " << i << '\n';
      //get hittime, shape, and point
      float hitTime = 0.0;
      /*for (Triangle triangle : triangles) { // Check all triangles
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
      }*/
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
      view.normalize();
      if (use_tri){
        hitPoint = hitTri.getMostRecentHitPoint();
        // std::cout << "normals?: " << hitTri.hasNormals() << "\n";
        normal = hitTri.getNormalAtPoint(hitPoint, view);
        material = hitTri.getMaterial();

      } else if (use_poly) {
        hitPoint = hitPoly.getMostRecentHitPoint();
        //std::cout << "normals?: " << hitTri.hasNormals() << "\n";
        normal = hitPoly.getNormalAtPoint(hitPoint, view);
        material = hitPoly.getMaterial();
      } else if (use_ellipsoid) {
        hitPoint = hitEllipsoid.getMostRecentHitPoint();
        normal = hitEllipsoid.getNormalAtPoint(hitPoint);
        material = hitEllipsoid.getMaterial();
      }
      normal.normalize();

      if (PRINT) {
        std::cout << "hitPoint X: " << hitPoint.getX() << ", Y: " << hitPoint.getY() << ", Z:" << hitPoint.getZ() << std::endl;
        std::cout << "normal X: " << normal.getX() << ", Y: " << normal.getY() << ", Z:" << normal.getZ() << std::endl;
        std::cout << "view X: " << view.getX() << ", Y: " << view.getY() << ", Z:" << view.getZ() << std::endl;
      }

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
        /*for (Triangle triangle : triangles) { // Check all triangles
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
        }*/
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
        /*for (Triangle triangle : triangles) { // Check all triangles
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
        }*/
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
      if (PRINT) {
        std::cout << "reflect X: " << reflect.getX() << ", Y: " << reflect.getY() << ", Z:" << reflect.getZ() << std::endl;
      }

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
    // if (i >= 550000 && i < 551000) {
    //   PRINT = true;
    // } else {
    //   PRINT = false;
    // }
    if (PRINT) {std::cout << "pixelnum: " << i << ": ";}

    //TO DO (lauren?)
    //get correct point through viewplane
    Point viewPoint = viewplane.getPixelCoords(i);
    // std::cout << "viewPoint X: " << viewPoint.getX() << ", Y:" << viewPoint.getY() << ", Z:" << viewPoint.getZ() << std::endl;
    
    // TODO semantics of ray definition
    Ray viewRay = Ray(viewPoint.getX(), viewPoint.getY(), viewPoint.getZ(), viewPoint.getX()-camera.getX(), viewPoint.getY()-camera.getY(), viewPoint.getZ()-camera.getZ());
    // std::cout << "viewRay X: " << viewRay.getDirectionX() << ", Y:" << viewRay.getDirectionY() << ", Z:" << viewRay.getDirectionZ() << std::endl;

    //call follow_ray with 5 as recursive depth
    Color pixelColor = follow_ray(viewRay, 5);
    // std::cout << "startColor R: " << startColor.get_r() << ", G: " << startColor.get_g() << ", G:" << startColor.get_b() << std::endl;
    
    // DONE lauren
    //add color to image object
    image.add_Color(i, pixelColor);
  }
  // std::cout << "END pixel loop" << std::endl;

  // std::cout << "START print to file" << std::endl;
  char fileName[] = {'o','u','t','I','m','g','.','p','n','g', '\0'};
  return image.printToFile(fileName);
}



void angleTest(float thetaX, float thetaY, float thetaZ){
  Ellipsoid* currEllipsoid = lastEllipsoid;
  while(currEllipsoid != NULL){
    if (currEllipsoid->isJoint()){
      currEllipsoid = currEllipsoid->getLeft();
      continue;
    }
    currEllipsoid->setTheta(thetaX, thetaY, thetaZ);
    currEllipsoid = currEllipsoid->getLeft();
  }
  cout << "angle test: updateTranformations\n";
  updateTranformations();
  do_ray_tracing();

}

void pinvTest(){
  MatrixXd m(3,2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(2,0) = 10;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);
  m(2,1) = 5;
  cout << m << endl;
  MatrixXd t = pinv(m);
  cout << "inverse: " << t << endl;
}

//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {
  // std::cout << "Hello World!";
  // runTests();
  if (argc == 1){
    //runTests();
  } else {

    std::cout << "START processArgs" << std::endl;
    processArgs(argc, argv);
    std::cout << "END processArgs" << std::endl;

    list<Point> curve;

    // TODO define curve

    curve.push_back(Point(18.0, 0.0, 0.0));

    for (Point target : curve) {

      std::cout << "START calculateJacobian" << std::endl;
      MatrixXd jacobian = calculateJacobian(); // calculate Jacobian based on current location of arm
      std::cout << "END calculateJacobian" << std::endl;
      
      std::cout << "START calculateAngles" << std::endl;
      calculateAngles(target, jacobian); // update all Ellipse objects so that angles get arm as close to target as possible
      std::cout << "END calculateAngles" << std::endl;

      updateTranformations();

      // TODO change filename for every timestep ?

      std::cout << "START do_ray_tracing" << std::endl;
      int success = do_ray_tracing();
      std::cout << "END do_ray_tracing: " << success << std::endl;
    }

    // std::cout << "START do_ray_tracing" << std::endl;
    // int success = do_ray_tracing();
    // std::cout << "END do_ray_tracing: " << success << std::endl;

    //angleTest(0.0, 0.0, 15.0);
    //angleTest(0.0, 15.0, 30.0);    
    //angleTest(0.0, 30.0, 45.0);
    //angleTest(0.0, 45.0, 60.0);
    //angleTest(0.0, 60.0, 90.0);
  }

  return 0;
}