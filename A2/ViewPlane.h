class ViewPlane{
public:
	ViewPlane();
	ViewPlane(float bx, float by, float tx, float ty, int pixelsHoriz, int pixelsVert); //ViewPlane defined by corners and number of pixels

	// TODO question of how big pixels are

	//instance methods
	float getBX();
	float getBY();
	float getTX();
	float getTY();
	int getNumPixelsHoriz();
	int getNumPixelsVert();
	int getNumPixels();

	Point getPixelCoors(int numPixel); // Returns coords of numPixel'th pixel
	// Coords are numbered 0 at (bx,by) to pixelsHoriz-1 at (tx,by) to pixelsHoriz*pixelsVert-1 at (tx,ty)

private:
	float bx;
	float by;
	float tx;
	float ty;
	int pixelsHoriz;
	int pixelsVert;
};