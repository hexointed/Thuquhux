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

void PhysObject::setMass(double mass){
	material.setDensity(mass/volume);
}
