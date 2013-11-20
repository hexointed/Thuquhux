/* 
 * File:   Material.cpp
 * Author: user
 * 
 * Created on May 29, 2013, 1:32 PM
 */

#include "Material.h"

Material::Material():
	_density{1},
	_restitution{}
{
}

//Material::Material(const Material& orig) {
//}

Material::~Material()
{
}

double& Material::density() {
	
	return _density;
}

double& Material::restitution(){
	return _restitution;
}
