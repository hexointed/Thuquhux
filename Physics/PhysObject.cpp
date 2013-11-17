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
	return _material.density();
}

Material& PhysObject::material(){
	return _material;
}

PointVector<>& PhysObject::position(){
	return _position;
}

PointVector<>& PhysObject::velocity(){
	return _velocity;
}
/*
Parametric_Surface& PhysObject::surface(){
	return surface;
}
*/
void PhysObject::calcVolume(){
	
}


void PhysObject::collision(PhysObject& obj1,PhysObject& obj2){
	obj1._velocity = (obj1._velocity.getMagnitude()*(obj1.density()*obj1._volume-obj2.density()*obj2._volume)+2.0*obj2.density()*obj2._volume*obj2._velocity.getMagnitude())/(obj1._volume*obj1.density() + obj2._volume*obj2.density()) * obj1._velocity.reflect(2.0*obj1._position-obj2._position).make_unit();
	obj2._velocity = (obj2._velocity.getMagnitude()*(obj2.density()*obj2._volume-obj1.density()*obj1._volume)+2.0*obj1.density()*obj1._volume*obj1._velocity.getMagnitude())/(obj2._volume*obj2.density() + obj1._volume*obj1.density()) * obj2._velocity.reflect(2.0*obj2._position-obj1._position).make_unit();
}
