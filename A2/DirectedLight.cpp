#include "DirectedLight.h"

DirectedLight::DirectedLight(){
	x, y, z, r, g, b = 0.0;
	activated = false;
}

DirectedLight::DirectedLight(float x, float y, float z, float r, float g, float b){
	this->x = x;
	this->y = y;
	this->z = z;
	this->r = r;
	this->g = g;
	this->b = b;
	this->lightVector;
	activated = true;
}

Color DirectedLight::getColor(){
	return Color(r, g, b);
}

Vector3 DirectedLight::getLightVector(float x, float y, float z){
	this->lightVector = new Vector3(-1*this->x, -1*this->y, -1*this->z);
	(*this->lightVector).normalize();
	return *this->lightVector;
}
	
Vector3 DirectedLight::getReflectionVector(Vector3 n){
	float tmpScalar;
	try{
		
		tmpScalar = 2*Vector3::dot(n, *lightVector);
		Vector3 tmp = Vector3::add(Vector3::scalarMultiply(*lightVector,-1.0), Vector3::scalarMultiply(n, tmpScalar));
		tmp.normalize();
		return tmp;
	}
	catch (char *exception){
		cout << exception;
	}
}

bool DirectedLight::IsActivated(){
	return activated;
}

void DirectedLight::scaleLocation(float scalar){
	x = x*scalar;
	y = y*scalar;
	z = z*scalar;
}

Color DirectedLight::getShadingOnObject(Material shp_mat, Point pnt, Vector3 normal, Vector3 view){
	//TO DO lauren

	
	// float RGB[3] = { 0.0, 0.0, 0.0 };

	// normal.normalize();
	// //find viewer vector
	// Vector3 viewerVector = Vector3(0.0, 0.0, 1.0);
	// //for each light
	// for (int i = 0; i < num_dir_lights; i++){
	// 	light = dir_lights[i];
 //    	light.scaleLocation(min(viewport.w, viewport.h)*0.9 / 2.0);
	// 	 if (light.IsActivated()){
	// 		Color lightColor = light.getColor();
	// 		float lightColorArr[3] = { lightColor.get_r(), lightColor.get_g(), lightColor.get_b() };
	// 		//calculate light vector
	// 		Vector3 lightVector = light.getLightVector(x, y, z);
	// 		//calculate reflection vector
	// 		Vector3 reflectVector = light.getReflectionVector(normal);
	// 		//for each color:
	// 		for (int j = 0; j <= 2; j++){
	// 			//DIFFUSE COMPONENT
	// 			//ASSUMPTION: i didn't normalize I
	// 			float diffuse = kd[j] * lightColorArr[j] * max(Vector3::dot(lightVector, normal), 0.f);
	// 			//SPECULAR COMPONENT
	// 			float specular = ks[j] * lightColorArr[j] * pow(max(Vector3::dot(reflectVector, viewerVector), 0.f), sp);
	// 			//AMBIENT COMPONENT
	// 			float ambient = ka[j] * lightColorArr[j];
	// 			 RGB[j] += diffuse + specular + ambient;
	// 		}
	// 	}
 //    	light.scaleLocation(1/(min(viewport.w, viewport.h)*0.9 / 2.0));
	// }



	return Color();
}