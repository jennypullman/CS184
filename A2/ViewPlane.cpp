#include "ViewPlane.h"
#include <iostream>

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

	// std::cout << "llx: " << llx << ", lly: " << lly << ", llz: " << llz << std::endl;
	// std::cout << "lrx: " << lrx << ", lry: " << lry << ", lrz: " << lrz << std::endl;
	// std::cout << "ulx: " << ulx << ", uly: " << uly << ", ulz: " << ulz << std::endl;
	// std::cout << "urx: " << urx << ", ury: " << ury << ", urz: " << urz << std::endl;

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
	
	// std::cout << "llx: " << llx << ", lly: " << lly << ", llz: " << llz << std::endl;
	// std::cout << "lrx: " << lrx << ", lry: " << lry << ", lrz: " << lrz << std::endl;
	// std::cout << "ulx: " << ulx << ", uly: " << uly << ", ulz: " << ulz << std::endl;
	// std::cout << "urx: " << urx << ", ury: " << ury << ", urz: " << urz << std::endl;
	
	int pixY = (int) numPixel/pixelsHoriz;
	int pixX = numPixel%pixelsHoriz;
    // std::cout << "pixY: " << pixY << ", pixX: " << pixX << "\n";

	float u = (float) pixX/pixelsHoriz;
	float v = (float) pixY/pixelsVert;
    // std::cout << "u: " << u << ", v: " << v << "\n";

	float px = u*(v*llx+(1-v)*ulx) + (1-u)*(v*lrx+(1-v)*urx);
	float py = u*(v*lly+(1-v)*uly) + (1-u)*(v*lry+(1-v)*ury);
	float pz = u*(v*llz+(1-v)*ulz) + (1-u)*(v*lrz+(1-v)*urz);
    std::cout << "px: " << px << ", py: " << py << ", pz: " << pz << "\n";

	return Point(px,py,pz);
}
// Coords are numbered 0 at (bx,by) to pixelsHoriz-1 at (tx,by) to pixelsHoriz*pixelsVert-1 at (tx,ty)
