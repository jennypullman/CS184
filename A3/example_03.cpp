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
// Simple init function
//****************************************************
void initScene(){
  // Nothing to do here for this simple example.
}


//****************************************************
// reshape viewport if the window is resized
//****************************************************
void myReshape(int w, int h) {
  viewport.w = w;
  viewport.h = h;
  
  glViewport (0,0,viewport.w,viewport.h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, viewport.w, 0, viewport.h);
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

  glMatrixMode(GL_MODELVIEW);             // indicate we are specifying camera transformations
  glLoadIdentity();               // make sure transformation is "zero'd"


  // Start drawing

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
    char c;
    string numSurfacesStr = "";
    int i = 0;
    while (!isspace(c)){
      c = line[i];
      numSurfacesStr += c;
      i++;
    }
    // std::cout << "NumSurfaces: " << numSurfaces << "\n";
    //get surfaces
    numSurfaces = stoi(numSurfacesStr);
    surfaces = new Surface[numSurfaces];
    
    int curCurveIndex = 0;
    int surfaceIndex = 0;
    Curve curves[4];
    while (getline(file, line)){

      if (isspace(line[0])){
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
        if (!isspace(c)){
          curPoint += c;
          lineIndex++;
        } else {
          coordinates[coordinateIndex] = stof(curPoint);
          curPoint = "";
          coordinateIndex++;
          while(isspace(c) && lineIndex < line.length()){
            c = line[++lineIndex];
          }
        }
        
      }
      if (coordinateIndex < 12){
        cout << "not enough points\n";
        //TODO
      }
      Point points[4];
      for (int i = 0; i < 4; i++){
        points[i] = Point(coordinates[i*4], coordinates[i*4+1], coordinates[i*4+2]);
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
    readBezierFile(fileName);
  }
}

void uniformTesselation(float du, float dv, int surfaceNum, Patch *patches){
  int patchIndex = 0;
  float u,v;
  Surface curSurface = surfaces[surfaceNum];
  for (u = 0; u+du < 1; u+= du){
    for (v = 0; v+dv < 1; v+= dv){
      patches[patchIndex++] = curSurface.determinePatch(u,v,du,dv);
    }
    if (v+dv > 1){
      patches[patchIndex++] = curSurface.determinePatch(u,v,du,1-(v+dv));
    }
  }
  if (u+du > 1){
    for (v = 0; v+dv < 1; v+= dv){
      patches[patchIndex++] = curSurface.determinePatch(u,v,1-(u+du),dv);
    }
    if (v+dv > 1){
      patches[patchIndex++] = curSurface.determinePatch(u,v,1-(u+du),1-(v+dv));
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
    int size = ceil(1/subdivision)*ceil(1/subdivision);
    Patch patches[size];
    uniformTesselation(subdivision, subdivision, surfaceIndex, patches);
    for (Patch patch : patches){
      if (option == ADAPTIVE){
        Triangle tri1 = Triangle(patch.getP1(), patch.getP2(), patch.getP3());
        Triangle tri2 = Triangle(patch.getP3(), patch.getP4(), patch.getP1());
        adaptiveTriangulation(tri1);
        adaptiveTriangulation(tri2);
      } else {
        //drawPatch
      }
    }
  }
}



//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {
  runTests();
  // //This initializes glut
  // glutInit(&argc, argv);

  // //This tells glut to use a double-buffered window with red, green, and blue channels 
  // glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  // // Initalize theviewport size
  // viewport.w = 400;
  // viewport.h = 400;

  // //The size and position of the window
  // glutInitWindowSize(viewport.w, viewport.h);
  // glutInitWindowPosition(0,0);
  // cout << argv[0] << "\n";
  // glutCreateWindow(argv[0]);

  // initScene();              // quick function to set up scene
  // processArgs(argc, argv);   // extra arguments from command

  // // cout << "ka_r: " << ka[0] << " ka_g: " << ka[1] << " ka_b: " << ka[2] << endl;
  // // cout << "kd_r: " << kd[0] << " kd_g: " << kd[1] << " kd_b: " << kd[2] << endl;
  // // cout << "ks_r: " << ks[0] << " ks_g: " << ks[1] << " ks_b: " << ks[2] << endl;
  // // cout << "sp: " << sp << endl;
  // // cout << "num_dir_lights: " << num_dir_lights << endl;
  // // cout << "num_point_lights: " << num_point_lights << endl;

  // glutDisplayFunc(myDisplay);       // function to run when its time to draw something
  // glutReshapeFunc(myReshape);       // function to run when the window gets resized

  // glutKeyboardFunc(myKeyboardFunc); // function to run on keyboard input - exit on spacebar

  // glutMainLoop();             // infinite loop that will keep drawing and resizing
  // // and whatever else

  return 0;
}