#include "Image.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h> // TODO decide if this is necessary
#include <png.h>

#include <iostream>


Image::Image(int height, int width) {
	h = height;
	w = width;
	numPixels = h*w;

	// zCoords = new float[height*width];
	rgb = new Color[height*width];

}

// int Image::get_z(int x, int y) const {
// 	return *(zCoords + x + w*y); // index (x,y) = y*(#elems/row) + x
// }


Color Image::get_Color(int pixelNum) {		// get rgb object for position (x,y) in rgb array
	return *(rgb + w*((int) pixelNum/w) + pixelNum%w); 
}

void Image::add_Color(int pixelNum, Color color) {		// set element for pixelNum'th pixel to color in rgb array
	*(rgb + w*((int) pixelNum/w) + pixelNum%w) = color;
}

int Image::printToFile(char* filename){
	int code = 0;
	FILE *fp;
	png_structp png_ptr;
	png_infop info_ptr;
	png_bytep row;

	// Open file for writing (binary mode)
	fp = fopen(filename, "wb");
	if (fp == NULL) {
		fprintf(stderr, "Could not open file %s for writing\n", filename);
		code = 1;
		goto finalise;
	}

	// Initialize write structure
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		fprintf(stderr, "Could not allocate write struct\n");
		code = 1;
		goto finalise;
	}

	// Initialize info structure
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fprintf(stderr, "Could not allocate info struct\n");
		code = 1;
		goto finalise;
	}

	png_init_io(png_ptr, fp);

	// Write header (8 bit colour depth)
	png_set_IHDR(png_ptr, info_ptr, w, h,
			8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	// Set title
	png_text title_text;
	title_text.compression = PNG_TEXT_COMPRESSION_NONE;
	title_text.key = "Title";
	title_text.text = filename;
	png_set_text(png_ptr, info_ptr, &title_text, 1);

	png_write_info(png_ptr, info_ptr);

	// Allocate memory for one row (3 bytes per pixel - RGB)
	row = (png_bytep) malloc(3 * w * sizeof(png_byte));

	// Write image data
	int x, y;
	for (y=0 ; y<h ; y++) {
		for (x=0 ; x<w ; x++) {
			row[x*3] = (int) fmin(255*rgb[y*w+x].get_r(),255);
			row[x*3+1] = (int) fmin(255*rgb[y*w+x].get_g(),255);
			row[x*3+2] = (int) fmin(255*rgb[y*w+x].get_b(),255);
			// std::cout << "Color r = "<< rgb[y*w+x].get_r() << std::endl;
			// std::cout << "Color r in row = "<< row[x*3] << std::endl;
		}
		png_write_row(png_ptr, row);
	}

	// End write
	png_write_end(png_ptr, NULL);

	finalise:
	if (fp != NULL) fclose(fp);
	if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
	if (row != NULL) free(row);

	return code;
}

int Image::getNumPixelsHoriz(){
	return w;
}
	
int Image::getNumPixelsVert(){
	return h;
}

int Image::getNumPixels() {
	return numPixels;
}