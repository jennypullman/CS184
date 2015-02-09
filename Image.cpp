#include "Image.h"

Image::Image(int height, int width) {
	h = height;
	w = width;

	zCoords = new float[height*width];
	rgb = new RGB[height*width];

	// TODO Initialize these arrays
}

int Image::get_z(int x, int y) const {
	return * (zCoords + x + w*y); // index (x,y) = y*(#elems/row) + x
}


RGB Image::get_rgb(int x, int y) const {
	return * (rgb + x + w*y); // index (x,y) = y*(#elems/row) + x
}

void Image::set_rgb(int x, int y, RGB color){
	*(rgb + x + w*y) = color; // index (x,y) = y*(#elems/row) + x
}