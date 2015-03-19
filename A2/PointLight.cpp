#include "PointLight.h"

PointLight::PointLight(){
	x, y, z, r, g, b, falloff = 0;
	activated = false;
}

PointLight::PointLight(float x, float y, float z, float r, float g, float b, int falloff){
	this->x = x;
	this->y = y;
	this->z = z;
	this->r = r;
	this->g = g;
	this->b = b;
	this->falloff = falloff;
	this->lightVector;
	activated = true;
}

Color PointLight::getColor(){
	return Color(r, g, b);
}

Vector3 PointLight::getLightVector(float x, float y, float z){
	this->lightVector = new Vector3(this->x - x, this->y - y, this->z - z);
	// (*this->lightVector).normalize();
	return *this->lightVector;
}

Vector3 PointLight::getReflectionVector(Vector3 n){
	float tmpScalar;
	try{

		tmpScalar = 2 * Vector3::dot(n, *lightVector);
		Vector3 tmp = Vector3::add(Vector3::scalarMultiply(*lightVector, -1.0), Vector3::scalarMultiply(n, tmpScalar));
		tmp.normalize();
		return tmp;
	}
	catch (char *exception){
		cout << exception;
	}
}

bool PointLight::IsActivated(){
	return activated;
}

void PointLight::scaleLocation(float scalar){
	x = x*scalar;
	y = y*scalar;
	z = z*scalar;
}

Color PointLight::getShadingOnObject(Material shp_mat, Point pnt, Vector3 normal, Vector3 view){
	//TO DO lauren
	Color color = Color(0.0,0.0,0.0);

	normal.normalize();
	//find viewer vector
	Vector3 viewVector = Vector3(view.getX(), view.getY(), view.getZ());
	viewVector.normalize();

	// TODO why were we doing this?
    // light.scaleLocation(min(viewport.w, viewport.h)*0.9 / 2.0);
	if (activated){
		//calculate light vector
		Vector3 lightVector = getLightVector(pnt.getX(), pnt.getY(), pnt.getZ());
		lightVector.normalize();
      	// std::cout << "lightVector X: " << lightVector.getX() << ", Y: " << lightVector.getY() << ", Z:" << lightVector.getZ() << std::endl;
		//calculate reflection vector
		Vector3 reflectVector = getReflectionVector(normal);
		reflectVector.normalize();
      	// std::cout << "reflectVector X: " << reflectVector.getX() << ", Y: " << reflectVector.getY() << ", Z:" << reflectVector.getZ() << std::endl;
		
      	float ambient = 0.0;

		//for red:
		//DIFFUSE COMPONENT
		//ASSUMPTION: i didn't normalize I
		float diffuse = shp_mat.getKdr() * r * max(Vector3::dot(lightVector, normal), 0.f);
		//SPECULAR COMPONENT
		float specular = shp_mat.getKsr() * r * pow(max(Vector3::dot(reflectVector, viewVector), 0.f), shp_mat.getKsp());
		//AMBIENT COMPONENT
		// float ambient = shp_mat.getKar() * r;
      	// std::cout << "R: kd: " << shp_mat.getKdr() << ", kd: " << shp_mat.getKsr() << ", ka:" << shp_mat.getKar() << std::endl;
      	// std::cout << "R: diffuse: " << diffuse << ", specular: " << specular << ", ambient:" << ambient << std::endl;
		color.update_r(diffuse + specular + ambient);

		//for green:
		//DIFFUSE COMPONENT
		//ASSUMPTION: i didn't normalize I
		diffuse = shp_mat.getKdg() * g * max(Vector3::dot(lightVector, normal), 0.f);
		//SPECULAR COMPONENT
		specular = shp_mat.getKsg() * g * pow(max(Vector3::dot(reflectVector, viewVector), 0.f), shp_mat.getKsp());
		//AMBIENT COMPONENT
		// ambient = shp_mat.getKag() * g;
      	// std::cout << "G: kd: " << shp_mat.getKdg() << ", kd: " << shp_mat.getKsg() << ", ka:" << shp_mat.getKag() << std::endl;
		// std::cout << "G: diffuse: " << diffuse << ", specular: " << specular << ", ambient:" << ambient << std::endl;
		color.update_g(diffuse + specular + ambient);

		//for blue:
		//DIFFUSE COMPONENT
		//ASSUMPTION: i didn't normalize I
		diffuse = shp_mat.getKdb() * b * max(Vector3::dot(lightVector, normal), 0.f);
		//SPECULAR COMPONENT
		specular = shp_mat.getKsb() * b * pow(max(Vector3::dot(reflectVector, viewVector), 0.f), shp_mat.getKsp());
		//AMBIENT COMPONENT
		// ambient = shp_mat.getKab() * b;
      	// std::cout << "B: kd: " << shp_mat.getKdb() << ", kd: " << shp_mat.getKsb() << ", ka:" << shp_mat.getKab() << std::endl;
		// std::cout << "B: diffuse: " << diffuse << ", specular: " << specular << ", ambient:" << ambient << std::endl;
		color.update_b(diffuse + specular + ambient);
		
	}

	// TODO ? light.scaleLocation(1/(min(viewport.w, viewport.h)*0.9 / 2.0));

	return color;
}

int PointLight::getFalloff() {
	return falloff;
}