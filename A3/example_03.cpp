#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include <time.h>
#include <math.h>


#define PI 3.14159265  // Should be used from mathlib
inline float sqr(float x) { return x*x; }

using namespace std;

#include <stdlib.h>
#include "Surface.h"
#include <cfloat>
#include <vector>
//****************************************************
// Some Classes
//****************************************************

class Viewport;

class Viewport {
  public:
    int w, h; // width and height
};


//****************************************************
// Global Variables
//****************************************************
Viewport  viewport;
const float DEFAULT = 0.1;
const int ADAPTIVE = 1;
const int UNIFORM = 0;

//command-line parameters
float subdivision;
float error;
int option;
Surface *surfaces;
int numSurfaces;
std::vector<Patch> patches;
std::vector<Triangle> triangles;
int patchesLength;


int decasteljauTest1(){
  Curve c = Curve(Point(0,0,0),Point(0,1,0), Point(1,1,0), Point(1,0,0));
  Point d = c.computeDecasteljau(0.5);
  if (d.getX() != 0.5 && d.getY() != 0.75 && d.getZ() != 0){
    //fail
    cout << "Failed decasteljauTest1.\n";
    return 0;
  }
  return 1;
}

void runTests(){
  int success = 0;
  int total;
  cout << "Running decasteljauTest1...\n";
  success += decasteljauTest1();
  total += 1;
  cout << "Total success: " << success << "/" << total << "\n";
}


//****************************************************
// reshape viewport if the window is resized
//****************************************************
void myReshape(int w, int h) {
  // viewport.w = w;
  // viewport.h = h;
  
  // glViewport (0,0,viewport.w,viewport.h);
  // glMatrixMode(GL_PROJECTION);
  // glLoadIdentity();
  // gluOrtho2D(0, viewport.w, 0, viewport.h);

  viewport.w = w;
  viewport.h = h;

  glViewport(0,0,viewport.w,viewport.h);// sets the rectangle that will be the window
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();                // loading the identity matrix for the screen

  //----------- setting the projection -------------------------
  // glOrtho sets left, right, bottom, top, zNear, zFar of the chord system


  // glOrtho(-1, 1 + (w-400)/200.0 , -1 -(h-400)/200.0, 1, 1, -1); // resize type = add
  // glOrtho(-w/400.0, w/400.0, -h/400.0, h/400.0, 1, -1); // resize type = center

  glOrtho(-5, 5, -5, 5, 5, -5);    // resize type = stretch
}

//****************************************************
// Simple init function
//****************************************************
void initScene(){
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Clear to black, fully transparent

  // glEnable(GL_CULL_FACE);
  // glEnable(GL_DEPTH_TEST);
  // glDepthMask(GL_TRUE);

  myReshape(viewport.w,viewport.h);
}


//****************************************************
// A routine to set a pixel by drawing a GL point.  This is not a
// general purpose routine as it assumes a lot of stuff specific to
// this example.
//****************************************************

void setPixel(int x, int y, GLfloat r, GLfloat g, GLfloat b) {
  glColor3f(r, g, b);
  glVertex2f(x + 0.5, y + 0.5);   // The 0.5 is to target pixel
  // centers 
  // Note: Need to check for gap
  // bug on inst machines.
}

//****************************************************
// function that does the actual drawing of stuff
//***************************************************
void myDisplay() {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);       // clear the color buffer
  // glClear(GL_COLOR_BUFFER_BIT);       // clear the color buffer


  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  // glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
  glMatrixMode(GL_MODELVIEW);             // indicate we are specifying camera transformations
  glLoadIdentity();               // make sure transformation is "zero'd"

  // Initialize lights
  glShadeModel(GL_FLAT);
  GLfloat light_pos[] = {0., 0., 1., 0.};
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, specular);

  // Set material
  GLfloat cyan[] = {0.f, .8f, .8f, 1.f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cyan);
  // glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);


  // Start drawing
  // glColor3f(1.0f, 1.0f, 1.0f);

  Patch currPatch;

  // std::cout<<"patches length: "<<patches.size()<<std::endl;
  // for (int i = 0; i < patchesLength; i++) {

  // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

  glBegin(GL_QUADS);
  for(std::vector<Patch>::iterator it = patches.begin() ; it != patches.end(); ++it) {
    
    // std::cout<<"drawing patch "<<i<<std::endl;
    // currPatch = patches[i];
    currPatch = *it;
    Point p1 = currPatch.getP1();
    Point p2 = currPatch.getP2();
    Point p3 = currPatch.getP3();
    Point p4 = currPatch.getP4();

    Vector3 n1 = currPatch.getN1();
    Vector3 n2 = currPatch.getN2();
    Vector3 n3 = currPatch.getN3();
    Vector3 n4 = currPatch.getN4();

    n1.normalize();
    n2.normalize();
    n3.normalize();
    n4.normalize();

    // p1.print();
    n1.print();
    // p2.print();
    n2.print();
    // p3.print();
    n3.print();
    // p4.print();
    n4.print();

    // // glNormal3f(n1.getX(), n1.getY(), n1.getZ());
    // glVertex3f(p1.getX(), p1.getY(), p1.getZ());
    
    // // glNormal3f(n2.getX(), n2.getY(), n2.getZ());
    // glVertex3f(p2.getX(), p2.getY(), p2.getZ());

    // // glNormal3f(n3.getX(), n3.getY(), n3.getZ());
    // glVertex3f(p3.getX(), p3.getY(), p3.getZ());

    // // glNormal3f(n4.getX(), n4.getY(), n4.getZ());
    // glVertex3f(p4.getX(), p4.getY(), p4.getZ());


// // switch z, y for testing purposes
    glNormal3f(n1.getX(), n1.getZ(), n1.getY());
    glVertex3f(p1.getX(), p1.getZ(), p1.getY());
    
    glNormal3f(n2.getX(), n2.getZ(), n2.getY());
    glVertex3f(p2.getX(), p2.getZ(), p2.getY());

    glNormal3f(n3.getX(), n3.getZ(), n3.getY());
    glVertex3f(p3.getX(), p3.getZ(), p3.getY());

    glNormal3f(n4.getX(), n4.getZ(), n4.getY());
    glVertex3f(p4.getX(), p4.getZ(), p4.getY());
    // glEnd();
  }
  glEnd();

  //   glBegin(GL_POLYGON);                         // draw diamond
  //   glVertex3f( 0.0f, 0.3f, 0.0f);               // top corner of diamond
  // glVertex3f( 0.3f, 0.0f, 0.0f);               // right corner of diamond
  // glVertex3f( 0.0f,-0.3f, 0.0f);               // bottom corner of diamond
  // glVertex3f(-0.3f, 0.0f, 0.0f);               // left corner of diamond
  //   glEnd();

  glFlush();
  glutSwapBuffers();          // swap buffers (we earlier set double buffer)
}

void myKeyboardFunc(unsigned char key, int x, int y) {
  switch(key) {
    case ' ':  exit(1);  // exit on space
    break;
  };
}

int readBezierFile(string fileName){
  fstream file;
  file.open(fileName);
  string line;
  if (file.is_open()){
    //get number of surfaces
    getline(file, line);
    std::cout << "line: " << line << std::endl;
    char c;
    string numSurfacesStr = "";
    int i = 0;
    while (!isspace(c)){
      c = line[i];
      numSurfacesStr += c;
      i++;
    }
    std::cout << "NumSurfacesStr: " << numSurfacesStr << "\n";
    //get surfaces
    numSurfaces = stoi(numSurfacesStr);
    std::cout << "NumSurfaces: " << numSurfaces << "\n";

    surfaces = new Surface[numSurfaces];
    
    int curCurveIndex = 0;
    int surfaceIndex = 0;
    Curve curves[4];
    while (getline(file, line)){
      std::cout << "line: " << line << std::endl;
      // std::cout << "line length: " << line.length() << std::endl;
      // if (isspace(line[0])){
      if (line.length() <= 1) {
        std::cout << "end line b/c space" << std::endl;
        surfaceIndex++;
        if (curCurveIndex < 4 && curCurveIndex != 0){
          cout << "not enough curves in patch\n";
          //TO DO
        }
        curCurveIndex = 0;
        continue;
      }
      char c;
      float coordinates[12];
      string curPoint = "";
      int coordinateIndex = 0;
      int lineIndex = 0;
      while (coordinateIndex < 12 && lineIndex < line.length()){
        c = line[lineIndex];
        // std::cout << "c: " << c <<std::endl;
        if (!isspace(c)){
          curPoint += c;
          lineIndex++;
        } else {
          if (curPoint.length() > 0){
            // std::cout << "cmurPoint: " << curPoint << std::endl;
            coordinates[coordinateIndex] = stof(curPoint);
            curPoint = "";
            coordinateIndex++;
            while(isspace(c) && lineIndex < line.length()){
              c = line[++lineIndex];
            }
          } else {
            lineIndex++;
          }
        }
        
      }
      if (coordinateIndex < 12){
        cout << "not enough points\n";
        //TODO
      }
      Point points[4];
      for (int i = 0; i < 4; i++){
        points[i] = Point(coordinates[i*3], coordinates[i*3+1], coordinates[i*3+2]);
      }
      curves[curCurveIndex++] = Curve(points[0], points[1], points[2], points[3]);

      if (curCurveIndex >= 4){
        surfaces[surfaceIndex] = Surface(curves[0], curves[1], curves[2], curves[3]);
        //curCurveIndex reset when getline just yields a newline
      }
    }
    if (surfaceIndex < numSurfaces){
      cout << "not the correct number of surfaces\n";
      //TO DO
    }
    file.close();
  } else {
    cout << "couldn't open file\n";
    //TO DO
  }
  //print surfaces:
  
  for (int i = 0; i < numSurfaces; i++){
    cout << "Surface " << i+1 << ": \n";
    surfaces[i].print();
  }
}



void processArgs(int argc, char *argv[]) {
  // cout << "argc: " << argc << "\n";
  // for (int i = argc - 1; i >= 0; i--) { 
  //   cout << argv[i] << "\n";
  // }
  string fileName;
  if (argc < 3 || argc > 4){
    cout << "messed\n";
    //TO DO
  }  else {
    fileName = argv[1];
    if (argc == 4){
      string thirdArg = argv[3];
      if (thirdArg.compare("-a") == 0){
        subdivision = DEFAULT;
        error = atof(argv[2]);
        option = ADAPTIVE;
      }
    } else {
      subdivision = atof(argv[2]);
      option = UNIFORM;
    }

    std::cout << "fileName: " << fileName <<std::endl;
    std::cout << "subdivision: " << subdivision << std::endl;
    std::cout << "option: " << option <<std::endl;

    readBezierFile(fileName);
  }
}

// tesselates one patch (group of 16 control points)
void uniformTesselation(float du, float dv, int surfaceNum, std::vector<Patch>& patches){
  // TODO add one normal for patch - might want compute normal function

  int patchIndex = 0;
  float u,v;
  Surface curSurface = surfaces[surfaceNum];
  for (u = 0; u+du <= 1; u+= du){
    // std::cout<<"U: " << u << std::endl;
    for (v = 0; v+dv <= 1; v+= dv){
      // std::cout<<"V: " << v << std::endl;
      // std::cout << "u: " << u << ", v: " << v << ", du: " << du << ", dv: " << dv << std::endl;
      patches.push_back(curSurface.determinePatch(u,v,du,dv));
      // std::cout<<"patches length: "<<patches.size()<<std::endl;

      // patches[patchIndex++] = curSurface.determinePatch(u,v,du,dv);
      // std::cout << "PRINTING FROM PATCH" << std::endl;
      // patches[patchIndex-1].getP4().print();
    }
    if (v < 1){
      // std::cout << "u: " << u << ", v: " << v << ", du: " << du << ", dv: " << (1-v) << std::endl;
      patches.push_back(curSurface.determinePatch(u,v,du,1-v));
      // std::cout<<"patches length: "<<patches.size()<<std::endl;
      // patches[patchIndex++] = curSurface.determinePatch(u,v,du,1-v);
    }
  }
  if (u < 1){
    for (v = 0; v+dv <= 1; v+= dv){
      // std::cout << "u: " << u << ", v: " << v << ", du: " << (1-u) << ", dv: " << dv << std::endl;
      patches.push_back(curSurface.determinePatch(u,v,1-u,dv));
      // std::cout<<"patches length: "<<patches.size()<<std::endl;
      // patches[patchIndex++] = curSurface.determinePatch(u,v,1-u,dv);
    }
    if (v < 1){
      // std::cout << "u: " << u << ", v: " << v << ", du: " << (1-u) << ", dv: " << (1-v) << std::endl;
      patches.push_back(curSurface.determinePatch(u,v,1-u,1-v));
      // std::cout<<"patches length: "<<patches.size()<<std::endl;
      // patches[patchIndex++] = curSurface.determinePatch(u,v,1-u,1-v);
    }
  }
}

void adaptiveTriangulation(Triangle tri, int surfaceNum){
  Surface curSurface = surfaces[surfaceNum];
  //check all midpoints:
  //compute all midpoints (will compare to actual points on curve)
  Point mid12 = tri.getMidpoint12();
  Point mid23 = tri.getMidpoint23();
  Point mid31 = tri.getMidpoint31();
  //compute all uv midpoints (will use to compute actual points on curve)
  UVPoint uvMid12 = tri.getUVMidpoint12();
  UVPoint uvMid23 = tri.getUVMidpoint23();
  UVPoint uvMid31 = tri.getUVMidpoint31();
  //compute actual midpoints using uv midpoints
  Point actualMid12 = curSurface.computeBezier(uvMid12.getU(), uvMid12.getV());
  Point actualMid23 = curSurface.computeBezier(uvMid23.getU(), uvMid23.getV());
  Point actualMid31 = curSurface.computeBezier(uvMid31.getU(), uvMid31.getV());
  //compute midpoint normals

  Vector3 mid12Normal = curSurface.computeNormal(uvMid12.getU(), uvMid12.getV());
  Vector3 mid23Normal = curSurface.computeNormal(uvMid23.getU(), uvMid23.getV());
  Vector3 mid31Normal = curSurface.computeNormal(uvMid31.getU(), uvMid31.getV());
  
  //compute distances from midpoints to actual midpoints to compute error
  float dist12 = mid12.getDistance(actualMid12);
  float dist23 = mid23.getDistance(actualMid23);
  float dist31 = mid31.getDistance(actualMid31);

  if (dist12 <= error){
    if (dist23 <= error){
      if (dist31 <= error){
	triangles.push_back(tri);
      }else{
	Vector3 normTri1 = curSurface.computeNormal(tri.getP1(), tri.getP2(), actualMid31, actualMid31);
	Vector3 normTri2 = curSurface.computeNormal(actualMid31, tri.getP2(), tri.getP3(), tri.getP3());
	Triangle tri1 = Triangle(tri.getP1(), tri.getP2(), actualMid31, tri.getUV1(), tri.getUV2(), uvMid31, normTri1, tri.getSN1(), tri.getSN2(), mid31Normal);
	Triangle tri2 = Triangle(actualMid31, tri.getP2(), tri.getP3(), uvMid31, tri.getUV2(), tri.getUV3(), normTri2, mid31Normal, tri.getSN2(), tri.getSN3());
	adaptiveTriangulation(tri1, surfaceNum);
	adaptiveTriangulation(tri2, surfaceNum);
      }
    }else {
      if (dist31 <= error){
	Vector3 normTri1 = curSurface.computeNormal(tri.getP1(), tri.getP2(), actualMid23, actualMid23);
	Vector3 normTri2 = curSurface.computeNormal(tri.getP1(), actualMid23, tri.getP3(), tri.getP3());
	Triangle tri1 = Triangle(tri.getP1(), tri.getP2(), actualMid23, tri.getUV1(), tri.getUV2(), uvMid23, normTri1, tri.getSN1(), tri.getSN2(), mid23Normal);
	Triangle tri2 = Triangle(tri.getP1(), actualMid23, tri.getP3(), tri.getUV1(), uvMid23, tri.getUV3(), normTri2, tri.getSN1(), mid23Normal, tri.getSN3());
	adaptiveTriangulation(tri1, surfaceNum);
	adaptiveTriangulation(tri2, surfaceNum);
      }else{
	Vector3 normTri1 = curSurface.computeNormal(tri.getP1(), tri.getP2(), actualMid31, actualMid31);
	Vector3 normTri2 = curSurface.computeNormal(actualMid31, tri.getP2(), actualMid23, actualMid23);
	Vector3 normTri3 = curSurface.computeNormal(actualMid31, actualMid23, tri.getP3(), tri.getP3());
	Triangle tri1 = Triangle(tri.getP1(), tri.getP2(), actualMid31, tri.getUV1(), tri.getUV2(), uvMid31, normTri1, tri.getSN1(), tri.getSN2(), mid31Normal);
	Triangle tri2 = Triangle(actualMid31, tri.getP2(), actualMid23, uvMid31, tri.getUV2(), tri.getUV3(), normTri2, mid31Normal, tri.getSN2(), mid23Normal);
	Triangle tri3 = Triangle(actualMid31, actualMid23, tri.getP3(), uvMid31, uvMid23, tri.getUV3(), normTri3, mid31Normal, mid23Normal, tri.getSN3());
	adaptiveTriangulation(tri1, surfaceNum);
	adaptiveTriangulation(tri2, surfaceNum);
	adaptiveTriangulation(tri3, surfaceNum);
      }
    }
  } else {
    if (dist23 <= error){
      if (dist31 <= error){
	Vector3 normTri1 = curSurface.computeNormal(tri.getP1(), actualMid12, tri.getP3(), tri.getP3());
	Vector3 normTri2 = curSurface.computeNormal(actualMid12, tri.getP2(), tri.getP3(), tri.getP3());
	Triangle tri1 = Triangle(tri.getP1(), actualMid12, tri.getP3(), tri.getUV1(), uvMid12, tri.getUV3(), normTri1, tri.getSN1(), mid12Normal, tri.getSN3());
	Triangle tri2 = Triangle(actualMid12, tri.getP2(), tri.getP3(), uvMid12, tri.getUV2(), tri.getUV3(), normTri2, mid12Normal, tri.getSN2(), tri.getSN3());
	adaptiveTriangulation(tri1, surfaceNum);
	adaptiveTriangulation(tri2, surfaceNum);
      }else{
	Vector3 normTri1 = curSurface.computeNormal(tri.getP1(), actualMid12, actualMid31, actualMid31);
	Vector3 normTri2 = curSurface.computeNormal(actualMid31, actualMid12, tri.getP3(), tri.getP3());
	Vector3 normTri3 = curSurface.computeNormal(actualMid12, tri.getP2(), tri.getP3(), tri.getP3());
	Triangle tri1 = Triangle(tri.getP1(), actualMid12, actualMid31, tri.getUV1(), uvMid12, uvMid31, normTri1, tri.getSN1(), mid12Normal, mid31Normal);
	Triangle tri2 = Triangle(actualMid31, actualMid12, tri.getP3(), uvMid31, uvMid12, tri.getUV3(), normTri2, mid31Normal, mid12Normal, tri.getSN3());
	Triangle tri3 = Triangle(actualMid12, tri.getP2(), tri.getP3(), uvMid12, tri.getUV2(), tri.getUV3(), normTri3, mid12Normal, tri.getSN2(), tri.getSN3());
	adaptiveTriangulation(tri1, surfaceNum);
	adaptiveTriangulation(tri2, surfaceNum);
	adaptiveTriangulation(tri3, surfaceNum);
      }
    }else {
      if (dist31 <= error){
	Vector3 normTri1 = curSurface.computeNormal(tri.getP1(), actualMid12, actualMid23, actualMid23);
	Vector3 normTri2 = curSurface.computeNormal(actualMid12, tri.getP2(), actualMid23, actualMid23);
	Vector3 normTri3 = curSurface.computeNormal(tri.getP1(), actualMid23, tri.getP3(), tri.getP3());
	Triangle tri1 = Triangle(tri.getP1(), actualMid12, actualMid23, tri.getUV1(), uvMid12, uvMid23, normTri1, tri.getSN1(), mid12Normal, mid23Normal);
	Triangle tri2 = Triangle(actualMid12, tri.getP2(), actualMid23, uvMid12, tri.getUV2(), uvMid23, normTri2, mid12Normal, tri.getSN2(), mid23Normal);
	Triangle tri3 = Triangle(tri.getP1(), actualMid23, tri.getP3(), tri.getUV1(), uvMid23, tri.getUV3(), normTri3, tri.getSN1(), mid23Normal, tri.getSN3());
	adaptiveTriangulation(tri1, surfaceNum);
	adaptiveTriangulation(tri2, surfaceNum);
	adaptiveTriangulation(tri3, surfaceNum);
      }else{
	Vector3 normTri1 = curSurface.computeNormal(tri.getP1(), actualMid12, actualMid31, actualMid31);
	Vector3 normTri2 = curSurface.computeNormal(actualMid12, tri.getP2(), actualMid23, actualMid23);
	Vector3 normTri3 = curSurface.computeNormal(actualMid31, actualMid23, tri.getP3(), tri.getP3());
	Vector3 normTri4 = curSurface.computeNormal(actualMid31, actualMid12, actualMid23, actualMid23);
	Triangle tri1 = Triangle(tri.getP1(), actualMid12, actualMid31, tri.getUV1(), uvMid12, uvMid31, normTri1, tri.getSN1(), mid12Normal, mid31Normal);
	Triangle tri2 = Triangle(actualMid12, tri.getP2(), actualMid23, uvMid12, tri.getUV2(), uvMid23, normTri2, mid12Normal, tri.getSN2(), mid23Normal);
	Triangle tri3 = Triangle(actualMid31, actualMid23, tri.getP3(), uvMid31, uvMid23, tri.getUV3(), normTri3, mid31Normal, mid23Normal, tri.getSN3());
	Triangle tri4 = Triangle(actualMid31, actualMid12, actualMid23, uvMid31, uvMid12, uvMid23, normTri4, mid31Normal, mid12Normal, mid23Normal);
	adaptiveTriangulation(tri1, surfaceNum);
	adaptiveTriangulation(tri2, surfaceNum);
	adaptiveTriangulation(tri3, surfaceNum);
	adaptiveTriangulation(tri4, surfaceNum);
      }
    }
  }
}

void makeTriangles(std::vector<Triangle>& triangles, int surfaceNum){
  Surface curSurface = surfaces[surfaceNum];
  Point surfacePoints[16];
  UVPoint uvPoints[16];
  Curve surfaceCurves[4];
  Vector3 smoothNormals[16];
  /*surfaceCurves[0] = curSurface.getCurve1();
  surfaceCurves[1] = curSurface.getCurve2();
  surfaceCurves[2] = curSurface.getCurve3();
  surfaceCurves[3] = curSurface.getCurve4();
  for (int i = 0; i < 4; i++){
    surfacePoints[i*4] = surfaceCurves[i].getP1();
    surfacePoints[i*4+1] = surfaceCurves[i].getP2();
    surfacePoints[i*4+2] = surfaceCurves[i].getP3();
    surfacePoints[i*4+3] = surfaceCurves[i].getP4();
    }*/
  for (float i = 0; i < 4.0; i+=1.0) {
    for (float j = 0; j < 4.0; j+=1.0) {
      int y = i;
      int x = j;
      uvPoints[y*4+x] = UVPoint(j/3, i/3);
      smoothNormals[y*4+x] = curSurface.computeNormal(j/3, i/3);
    }
  }
  
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      surfacePoints[i*4+j] = curSurface.computeBezier(uvPoints[i*4+j].getU(), uvPoints[i*4+j].getV());
    }
  }

  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      Vector3 flatNorm1 = curSurface.computeNormal(surfacePoints[i*4+j], surfacePoints[(i+1)*4+j], surfacePoints[(i+1)*4+j+1], surfacePoints[(i+1)*4+j+1]);
      Vector3 flatNorm2 = curSurface.computeNormal(surfacePoints[i*4+j], surfacePoints[(i+1)*4+j+1], surfacePoints[i*4+j+1], surfacePoints[i*4+j+1]);
      triangles.push_back(Triangle(surfacePoints[i*4+j], surfacePoints[(i+1)*4+j], surfacePoints[(i+1)*4+j+1], uvPoints[i*4+j], uvPoints[(i+1)*4+j], uvPoints[(i+1)*4+j+1],
				   flatNorm1, smoothNormals[i*4+j], smoothNormals[(i+1)*4+j], smoothNormals[(i+1)*4+j+1]));
      triangles.push_back(Triangle(surfacePoints[i*4+j], surfacePoints[(i+1)*4+j+1], surfacePoints[i*4+j+1], uvPoints[i*4+j], uvPoints[(i+1)*4+j+1], uvPoints[i*4+j+1], 
				   flatNorm2, smoothNormals[i*4+j], smoothNormals[(i+1)*4+j+1], smoothNormals[i*4+j+1]));
    }
  }
  
}

void drawSurfaces(){
  for (int surfaceIndex = 0; surfaceIndex < numSurfaces;surfaceIndex++){
    if (option == UNIFORM) {
      // std::cout << "using UNIFORM" << std::endl;
      int size = ceil(1/subdivision)*ceil(1/subdivision); //TODO check here
      patchesLength = size;
      // patches = std::vector<Patch>(patchesLength);
      // if (surfaceIndex == 1){
        uniformTesselation(subdivision, subdivision, surfaceIndex, patches);
        // patches[0].getP3().print();
      // }
    } else {
      // TODO fill in ADAPTIVE tesselation
      std::vector<Triangle> triangles;
      makeTriangles(triangles, surfaceIndex);
      Triangle currTriangle;
      for(std::vector<Triangle>::iterator it = triangles.begin() ; it != triangles.end(); ++it) {
	currTriangle = *it;
	adaptiveTriangulation(currTriangle, surfaceIndex);
      }
	
      
    }
    // for (Patch patch : patches){
    //   if (option == ADAPTIVE){
    //     // TODO check points taken in correct order
    //     Triangle tri1 = Triangle(patch.getP1(), patch.getP2(), patch.getP3());
    //     Triangle tri2 = Triangle(patch.getP3(), patch.getP4(), patch.getP1());
    //     adaptiveTriangulation(tri1);
    //     adaptiveTriangulation(tri2);
    //   } else {
    //     //drawPatch
    //   }
    // }
  }
}



//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {
  runTests();
  //This initializes glut
  glutInit(&argc, argv);

  //This tells glut to use a double-buffered window with red, green, and blue channels 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  

  // Initalize theviewport size
  viewport.w = 800;
  viewport.h = 800;

  //The size and position of the window
  glutInitWindowSize(viewport.w, viewport.h);
  glutInitWindowPosition(0,0);
  cout << argv[0] << "\n";
  glutCreateWindow(argv[0]);

  initScene();              // quick function to set up scene
  processArgs(argc, argv);   // extra arguments from command

  drawSurfaces();

  // // cout << "ka_r: " << ka[0] << " ka_g: " << ka[1] << " ka_b: " << ka[2] << endl;
  // // cout << "kd_r: " << kd[0] << " kd_g: " << kd[1] << " kd_b: " << kd[2] << endl;
  // // cout << "ks_r: " << ks[0] << " ks_g: " << ks[1] << " ks_b: " << ks[2] << endl;
  // // cout << "sp: " << sp << endl;
  // // cout << "num_dir_lights: " << num_dir_lights << endl;
  // // cout << "num_point_lights: " << num_point_lights << endl;

  glutDisplayFunc(myDisplay);       // function to run when its time to draw something
  glutReshapeFunc(myReshape);       // function to run when the window gets resized

  glutKeyboardFunc(myKeyboardFunc); // function to run on keyboard input - exit on spacebar

  glutMainLoop();             // infinite loop that will keep drawing and resizing
  // and whatever else

  return 0;
}
