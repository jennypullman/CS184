#include "RGB.h"

RGB::RGB(float red, float green, float blue) {
	r = red;
	g = green;
	b = blue;
}

RGB RGB::rgb_add(RGB color1, RGB color2) const {
	return RGB(color1.get_r()+color2.get_r(), color1.get_g()+color2.get_g(), color1.get_b()+color2.get_b());
}

RGB RGB::rgb_sub(RGB color1, RGB color2) const {
	return RGB(color1.get_r()-color2.get_r(), color1.get_g()-color2.get_g(), color1.get_b()-color2.get_b());
}

RGB RGB::rgb_mult(RGB color1, RGB color2) const {
	return RGB(color1.get_r()*color2.get_r(), color1.get_g()*color2.get_g(), color1.get_b()*color2.get_b());
}

RGB RGB::scalar_mult(RGB color, float scalar) const {
	return RGB(color.get_r()*scalar, color.get_g()*scalar, color.get_b()*scalar);
}

RGB RGB::scalar_mult(RGB color, float scalar) const {
	if (0 == scalar) { // Can't divide by 0
		scalar = 1.0;
	}
	return RGB(color.get_r()/scalar, color.get_g()/scalar, color.get_b()/scalar);
}

void RGB::udpate_r(float red){
	r = red;
}

void RGB::udpate_g(float green){
	g = green;
}

void RGB::udpate_b(float blue){
	b = blue;
}

float RGB::get_r(){
	return r;
}

float RGB::get_g(){
	return g;
}

float RGB::get_b(){
	return b;
}