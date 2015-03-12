#include "Material.h"

Material::Material(){
}

Material::Material(float kar, float kag, float kab, 
			float kdr, float kdg, float kdb, float ksr, float ksg, float ksb, float ksp,
			float krr, float krg, float krb){
	this->kar = kar;
	this->kag = kag;
	this->kab = kab;
	this->kdr = kdr;
	this->kdg = kdg;
	this->kdb = kdb;
	this->ksr = ksr;
	this->ksg = ksg;
	this->ksb = ksb;
	this->ksp = ksp;
	this->krr = krr;
	this->krg = krg;
	this->krb = krb;
}

float Material::getKar(){
	return kar;
}
float Material::getKag(){
	return kag;
}
float Material::getKab(){
	return kab;
}
float Material::getKdr(){
	return kdr;
}
float Material::getKdb(){
	return kdb;
}
float Material::getKsr(){
	return ksr;
}
float Material::getKsb(){
	return ksb;
}
float Material::getKsp(){
	return ksp;
}
float Material::getKrr(){
	return krr;
}
float Material::getKrg(){
	return krg;
}
float Material::getKrb(){
	return krb;
}