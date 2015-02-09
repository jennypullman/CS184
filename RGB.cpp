#include "RGB.h"

RGB::RGB(float red, float green, float blue) {
	r = red;
	g = green;
	b = blue;
}

RGB RBG::rgb_add(RGB color1, RGB color2) const {
	return RGB(color1.get_r()+color2.get_r(), color1.get_g()+color2.get_g(), color1.get_b()+color2.get_b());
}

RGB RBG::rgb_sub(RGB color1, RGB color2) const {
	return RGB(color1.get_r()-color2.get_r(), color1.get_g()-color2.get_g(), color1.get_b()-color2.get_b());
}

RGB RBG::rgb_mult(RGB color1, RGB color2) const {
	return RGB(color1.get_r()*color2.get_r(), color1.get_g()*color2.get_g(), color1.get_b()*color2.get_b());
}

RGB scalar_mult(RGB color, float scalar) const {
	return RGB(color.get_r()*scalar, color.get_g()*scalar, color.get_b()*scalar);
}

RGB scalar_mult(RGB color, float scalar) const {
	if (0 == scalar) { // Can't divide by 0
		scalar = 1.0;
	}
	return RGB(color.get_r()/scalar, color.get_g()/scalar, color.get_b()/scalar);
}

void udpate_r(float red){
	r = red;
}

void udpate_g(float green){
	g = green;
}

void udpate_b(float blue){
	b = blue;
}

float get_r(){
	return r;
}

float get_g(){
	return g;
}

float get_b(){
	return b;
}