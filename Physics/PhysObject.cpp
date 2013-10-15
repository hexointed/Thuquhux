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
	
}

void PhysObject::collision(PhysObject& obj1,PhysObject& obj2){
	obj1.velocity = (obj1.velocity*(obj1.density()*obj1.volume-obj2.density()*obj2.volume)+2*obj2.density()*obj2.volume*obj2.velocity.getMagnitude()) * obj1.velocity.reflect(2*obj1.position-obj2.position).make_unit()
	obj2.velocity = (obj2.velocity*(obj2.density()*obj2.volume-obj1.density()*obj1.volume)+2*obj1.density()*obj1.volume*obj1.velocity.getMagnitude()) * obj2.velocity.reflect(2*obj2.position-obj1.position).make_unit()
}
