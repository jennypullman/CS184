//#include "Color.h"

class Image {
  public:
    Image(int height, int width);                         // constructor; initialize the height and width in pixels

    Color get_Color(int pixelNum);                            // get rgb object for position (x,y) in rgb array
    void add_Color(int pixelNum, Color color);                // set element for pixelNum'th pixel to color in rgb array

    int printToFile(char* filename);                                   // output rgb array as an image file TODO determine format and return value

    int getNumPixelsHoriz();
    int getNumPixelsVert();
    int getNumPixels();

  private:
    Color *rgb;                    						  // rgb points to dynamically allocated array that gives Color object for each (x,y) pair
    int h;                                                // height
    int w;                                                // width   
    int numPixels;            
};