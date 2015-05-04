#include "Transformation.h"

class ViewPlane{
public:
	ViewPlane();
	ViewPlane(float llx, float lly, float llz, float lrx, float lry, float lrz, float ulx, float uly, float ulz, float urx, float ury, float urz, int pixelsHoriz, int pixelsVert); //ViewPlane defined by corners and number of pixels

	// TODO question of how big pixels are

	//instance methods
	float getLLX();
	float getLLY();
	float getLLZ();
	float getLRX();
	float getLRY();
	float getLRZ();
	float getULX();
	float getULY();
	float getULZ();
	float getURX();
	float getURY();
	float getURZ();
	int getNumPixelsHoriz();
	int getNumPixelsVert();
	int getNumPixels();

	Point getPixelCoords(int numPixel); // Returns coords of numPixel'th pixel
	// Ray getRayThroughPixel(int numPixel, Camera cam); // Return Ray from camera through center of numPixel'th pixel
	// Coords are numbered 0 at (bx,by) to pixelsHoriz-1 at (tx,by) to pixelsHoriz*pixelsVert-1 at (tx,ty)

private:
	float llx, lly, llz, lrx, lry, lrz, ulx, uly, ulz, urx, ury, urz;
	int pixelsHoriz;
	int pixelsVert;
	int numPixels;
};