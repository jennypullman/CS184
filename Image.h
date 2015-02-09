#include "Color.h"

class Image {
  public:
    Image(int height, int width);                         // constructor; initialize the height and width

    int get_z(int x, int y) const;                              // get z position for position (x,y) in zCoords array

    Color get_rgb(int x, int y) const;                            // get rgb object for position (x,y) in rgb array
    void set_rgb(int x, int y, Color color);                // set element for position (x,y) to color in rgb array

  private:
    float *zCoords;                      			      // zCoords points to dynamically allocated array that gives z coord for each (x,y) pair
    Color *rgb;                    						  // rgb points to dynamically allocated array that gives rgb object for each (x,y) pair
    int h;                                                // height
    int w;                                                // width               
};