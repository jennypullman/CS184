#include "AmbientLight.h"

AmbientLight::AmbientLight(){
	activated = false;
}

AmbientLight::AmbientLight(float red, float green, float blue){
	r = red;
	g = green;
	b = blue;
	activated = true;
}

Color AmbientLight::getColor(){
	return Color(this->r, this->g, this->b);
}

Vector3 AmbientLight::getLightVector(float x, float y, float z){
	return Vector3();
}

Vector3 AmbientLight::getReflectionVector(Vector3 n){
	return Vector3();
}

bool AmbientLight::IsActivated(){
	return activated;
}

void AmbientLight::scaleLocation(float scalar){

}

Color AmbientLight::getShadingOnObject(Material shp_mat, Point pnt, Vector3 normal, Vector3 view){
	//TO DO lauren
	// TODO correct behavior? Only does ambient component
	Color color = Color(0.0,0.0,0.0);

	// TODO why were we doing this?
    // light.scaleLocation(min(viewport.w, viewport.h)*0.9 / 2.0);
	if (activated){

		//for red:
		color.update_r(shp_mat.getKar() * r);

		//for green:
		color.update_g(shp_mat.getKag() * g);

		//for blue:
		color.update_b(shp_mat.getKab() * b);
		
	}

	// TODO ? light.scaleLocation(1/(min(viewport.w, viewport.h)*0.9 / 2.0));

	return color;
}