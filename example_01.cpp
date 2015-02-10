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
#include "Light.h"
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
Viewport	viewport;
float ka_r, ka_g, ka_b = 0.0;
float kd_r, kd_g, kd_b = 0.0;
float ks_r, ks_g, ks_b = 0.0;
float sp = 0.0;
Light dir_lights[5];
int num_dir_lights = 0;
Light point_lights[5];
int num_point_lights = 0;



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
// Draw a filled circle.  
//****************************************************


void circle(float centerX, float centerY, float radius) {
  // Draw inner circle
  glBegin(GL_POINTS);

  // We could eliminate wasted work by only looping over the pixels
  // inside the sphere's radius.  But the example is more clear this
  // way.  In general drawing an object by loopig over the whole
  // screen is wasteful.

  int i,j;  // Pixel indices

  int minI = max(0,(int)floor(centerX-radius));
  int maxI = min(viewport.w-1,(int)ceil(centerX+radius));

  int minJ = max(0,(int)floor(centerY-radius));
  int maxJ = min(viewport.h-1,(int)ceil(centerY+radius));


  for (i=0;i<viewport.w;i++) {
    for (j=0;j<viewport.h;j++) {

      // Location of the center of pixel relative to center of sphere
      float x = (i+0.5-centerX);
      float y = (j+0.5-centerY);

      float dist = sqrt(sqr(x) + sqr(y));

      if (dist<=radius) {

        // This is the front-facing Z coordinate
        float z = sqrt(radius*radius-dist*dist);

		//TO DO
		//initialize R, G, B to 0.0
		//find normal
		//find viewer vector
		//for each light
		//calculate light vector
		//calculate reflection vector
		//for each color:
		//DIFFUSE COMPONENT
		//compute diffuse component, add to respective float color
		//SPECULAR COMPONENT
		//compute spec
		//AMBIENT COMPONENT
		//compute ambient

		
        setPixel(i,j, 1.0, 0.0, 0.0);

        // This is amusing, but it assumes negative color values are treated reasonably.
        // setPixel(i,j, x/radius, y/radius, z/radius );
      }


    }
  }


  glEnd();
}
//****************************************************
// function that does the actual drawing of stuff
//***************************************************
void myDisplay() {

  glClear(GL_COLOR_BUFFER_BIT);				// clear the color buffer

  glMatrixMode(GL_MODELVIEW);			        // indicate we are specifying camera transformations
  glLoadIdentity();				        // make sure transformation is "zero'd"


  // Start drawing
  circle(viewport.w / 2.0 , viewport.h / 2.0 , min(viewport.w, viewport.h)*0.9 / 2.0);

  glFlush();
  glutSwapBuffers();					// swap buffers (we earlier set double buffer)
}

void handleKA(int argc, char *argv[], int start) {
  // cout << "ka" << "\n";
  if (start+2 >= argc) {
    // TODO input error
  }

  ka_r = atof(argv[start]);
  ka_b = atof(argv[start+1]);
  ka_g = atof(argv[start+2]);
}

void handleKD(int argc, char *argv[], int start) {
  // cout << "kd" << "\n";
  if (start+2 >= argc) {
    // TODO input error
  }

  kd_r = atof(argv[start]);
  kd_b = atof(argv[start+1]);
  kd_g = atof(argv[start+2]);
}

void handleKS(int argc, char *argv[], int start) {
  // cout << "ks" << "\n";
  if (start+2 >= argc) {
    // TODO input error
  }

  ks_r = atof(argv[start]);
  ks_b = atof(argv[start+1]);
  ks_g = atof(argv[start+2]);
}

void handleSP(int argc, char *argv[], int start) {
  // cout << "sp" << "\n";
  if (start >= argc) {
    // TODO input error
  }

  sp = atof(argv[start]);
}

void handlePL(int argc, char *argv[], int start) {
  // cout << "pl" << "\n";
  if (start+5 >= argc) {
    // TODO input error
  }

  if (num_point_lights < 5) {
    point_lights[num_point_lights] = Light(atof(argv[start]), atof(argv[start+1]), atof(argv[start+2]), atof(argv[start+3]), atof(argv[start+4]), atof(argv[start+5]), false);
    num_point_lights++;
  }
}

void handleDL(int argc, char *argv[], int start) {
  // cout << "dl" << "\n";
  if (start+5 >= argc) {
    // TODO input error
  }

  if (num_dir_lights < 5) {
    dir_lights[num_dir_lights] = Light(atof(argv[start]), atof(argv[start+1]), atof(argv[start+2]), atof(argv[start+3]), atof(argv[start+4]), atof(argv[start+5]), true);
    num_dir_lights++;
  }
}

void processArgs(int argc, char *argv[]) {
  // cout << "argc: " << argc << "\n";
  // for (int i = argc - 1; i >= 0; i--) { 
  //   cout << argv[i] << "\n";
  // }
  string arg;
  for (int i = 1; i < argc; i++) {
    arg = argv[i];
    if (arg[0] != '-') {
      continue;
    }

    if (arg.compare("-ka") == 0){
      // cout << "ka" << "\n";
      handleKA(argc, argv, i+1);
    }
    
    if (arg.compare("-kd") == 0){
      // cout << "kd" << "\n";
      handleKD(argc, argv, i+1);
    }

    if (arg.compare("-ks") == 0){
      // cout << "ks" << "\n";
      handleKS(argc, argv, i+1);
    }

    if (arg.compare("-sp") == 0){
      // cout << "sp" << "\n";
      handleSP(argc, argv, i+1);
    }

    if (arg.compare("-pl") == 0){
      // cout << "pl" << "\n";
      handlePL(argc, argv, i+1);
    }

    if (arg.compare("-dl") == 0){
      // cout << "dl" << "\n";
      handleDL(argc, argv, i+1);
    }
  }
}


//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
int main(int argc, char *argv[]) {
  //This initializes glut
  glutInit(&argc, argv);

  //This tells glut to use a double-buffered window with red, green, and blue channels 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  // Initalize theviewport size
  viewport.w = 400;
  viewport.h = 400;

  //The size and position of the window
  glutInitWindowSize(viewport.w, viewport.h);
  glutInitWindowPosition(0,0);
  glutCreateWindow(argv[0]);

  initScene();							// quick function to set up scene
  processArgs(argc, argv);   // extra arguments from command

  // cout << "ka_r: " << ka_r << " ka_g: " << ka_g << " ka_b: " << ka_b << endl;
  // cout << "kd_r: " << kd_r << " kd_g: " << kd_g << " kd_b: " << kd_b << endl;
  // cout << "ks_r: " << ks_r << " ks_g: " << ks_g << " ks_b: " << ks_b << endl;
  // cout << "sp: " << sp << endl;
  // cout << "num_dir_lights: " << num_dir_lights << endl;
  // cout << "num_point_lights: " << num_point_lights << endl;

  glutDisplayFunc(myDisplay);				// function to run when its time to draw something
  glutReshapeFunc(myReshape);				// function to run when the window gets resized

  glutMainLoop();							// infinite loop that will keep drawing and resizing
  // and whatever else

  return 0;
}








