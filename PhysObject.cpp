/* 
 * File:   PhysObject.cpp
 * Author: elias
 * 
 * Created on April 28, 2013, 6:59 PM
 */

#include "PhysObject.h"
#include "Material.h"

PhysObject::PhysObject() {
}

PhysObject::PhysObject(const PhysObject& /*orig*/) {
}

PhysObject::~PhysObject() {
}

double& PhysObject::density(){
	return material.density();
}

Material& PhysObject::material(){
	return material;
}

PointVector& PhysObject::position(){
	return position;
}

PointVector& PhysObject::velocity(){
	return velocity;
}

Parametric_Surface& PhysObject::surface(){
	return surface;
}

void PhysObject::calcVolume(){
	
}

void PhysObject::unite(PhysObject a){
	surface.
}

void PhysObject::collision(PhysObject& obj1,PhysObject& obj2){
	obj1.velocity
}
