#include "ViewPlane.h"

ViewPlane::ViewPlane(){

}
ViewPlane::ViewPlane(float llx, float lly, float llz, float lrx, float lry, float lrz, 
		float ulx, float uly, float ulz, float urx, float ury, float urz, int pixelsHoriz, int pixelsVert){
	this->llx = llx;
	this->lly = lly;
	this->llz = llz;
	this->lrx = lrx;
	this->lry = lry;
	this->lrz = lrz;
	this->ulx = ulx;
	this->uly = uly;
	this->ulz = ulz;
	this->urx = urx;
	this->ury = ury;
	this->urz = urz;
	this->pixelsHoriz = pixelsHoriz;
	this->pixelsVert = pixelsVert;
	this->numPixels = pixelsVert*pixelsHoriz;

}
// TODO question of how big pixels are

//instance methods
float ViewPlane::getLLX(){
	return llx;
}
float ViewPlane::getLLY(){
	return lly;
}
float ViewPlane::getLLZ(){
	return llz;
}
float ViewPlane::getLRX(){
	return lrx;
}
float ViewPlane::getLRY(){
	return lry;
}
float ViewPlane::getLRZ(){
	return lrz;
}
float ViewPlane::getULX(){
	return ulx;
}
float ViewPlane::getULY(){
	return uly;
}
float ViewPlane::getULZ(){
	return ulz;
}
float ViewPlane::getURX(){
	return urx;
}
float ViewPlane::getURY(){
	return ury;
}
float ViewPlane::getURZ(){
	return urz;
}
int ViewPlane::getNumPixelsHoriz(){
	return pixelsHoriz;
}
int ViewPlane::getNumPixelsVert(){
	return pixelsVert;
}
int ViewPlane::getNumPixels(){
	return numPixels;
}

Point ViewPlane::getPixelCoords(int numPixel){
	int pixY = (int) numPixel/pixelsHoriz;
	int pixX = numPixel%pixelsHoriz;

	float u = pixX/pixelsHoriz;
	float v = pixY/pixelsVert;

	float px = u*(v*llx+(1-v)*ulx) + (1-u)*(v*lrx+(1-v)*urx);
	float py = u*(v*lly+(1-v)*uly) + (1-u)*(v*lry+(1-v)*ury);
	float pz = u*(v*llz+(1-v)*ulz) + (1-u)*(v*lrz+(1-v)*urz);

	return Point(px,py,pz);
}
// Coords are numbered 0 at (bx,by) to pixelsHoriz-1 at (tx,by) to pixelsHoriz*pixelsVert-1 at (tx,ty)
