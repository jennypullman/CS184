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

  glOrtho(-1, 1, -1, 1, 1, -1);    // resize type = stretch
}

//****************************************************
// Simple init function
//****************************************************
void initScene(){
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Clear to black, fully transparent

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

  glClear(GL_COLOR_BUFFER_BIT);       // clear the color buffer

  // glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
  glMatrixMode(GL_MODELVIEW);             // indicate we are specifying camera transformations
  glLoadIdentity();               // make sure transformation is "zero'd"


  // Start drawing
  glColor3f(1.0f, 1.0f, 1.0f);

  Patch currPatch;

  std::cout<<"patches length: "<<patches.size()<<std::endl;
  patches[0].getP3().print();
  // for (int i = 0; i < patchesLength; i++) {
  for(std::vector<Patch>::iterator it = patches.begin() ; it != patches.end(); ++it) {
    glBegin(GL_POLYGON);
    // std::cout<<"drawing patch "<<i<<std::endl;
    // currPatch = patches[i];
    currPatch = *it;
    Point p = currPatch.getP1();
    p.print();
    glVertex3f(p.getX(), p.getY(), p.getZ());
    p = currPatch.getP2();
    p.print();
    glVertex3f(p.getX(), p.getY(), p.getZ());
    p = currPatch.getP3();
    p.print();
    glVertex3f(p.getX(), p.getY(), p.getZ());
    p = currPatch.getP4();
    p.print();
    glVertex3f(p.getX(), p.getY(), p.getZ());
    glEnd();
  }

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

void adaptiveTriangulation(Triangle tri){
  //check all midpoints
  //subdivide if bad, recursively call adaptiveTriangulation on subdivisions
  //draw if all good
}

void drawSurfaces(){
  for (int surfaceIndex = 0; surfaceIndex < numSurfaces;surfaceIndex++){
    if (option == UNIFORM) {
      // std::cout << "using UNIFORM" << std::endl;
      int size = ceil(1/subdivision)*ceil(1/subdivision); //TODO check here
      patchesLength = size;
      // patches = std::vector<Patch>(patchesLength);
      // if (surfaceIndex == 0){
        uniformTesselation(subdivision, subdivision, surfaceIndex, patches);
        // patches[0].getP3().print();
      // }
    } else {
      // TODO fill in ADAPTIVE tesselation
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