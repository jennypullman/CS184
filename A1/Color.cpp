#include "Color.h"

Color::Color(float red, float green, float blue) {
	r = red;
	g = green;
	b = blue;
}
Color::Color() {
	r = g = b = 0.0;
}

Color Color::rgb_add(Color color1, Color color2){
	return Color(color1.get_r() + color2.get_r(), color1.get_g() + color2.get_g(), color1.get_b() + color2.get_b());
}

Color Color::rgb_sub(Color color1, Color color2){
	return Color(color1.get_r() - color2.get_r(), color1.get_g() - color2.get_g(), color1.get_b() - color2.get_b());
}

Color Color::rgb_mult(Color color1, Color color2){
	return Color(color1.get_r()*color2.get_r(), color1.get_g()*color2.get_g(), color1.get_b()*color2.get_b());
}

Color Color::scalar_mult(Color color, float scalar){
	return Color(color.get_r()*scalar, color.get_g()*scalar, color.get_b()*scalar);
}

Color Color::scalar_div(Color color, float scalar){
	if (0 == scalar) { // Can't divide by 0
		scalar = 1.0;
	}
	return Color(color.get_r() / scalar, color.get_g() / scalar, color.get_b() / scalar);
}

void Color::udpate_r(float red){
	r = red;
}

void Color::udpate_g(float green){
	g = green;
}

void Color::udpate_b(float blue){
	b = blue;
}

float Color::get_r(){
	return r;
}

float Color::get_g(){
	return g;
}

float Color::get_b(){
	return b;
}