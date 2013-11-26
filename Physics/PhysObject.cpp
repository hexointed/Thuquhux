/* 
 * File:   PhysObject.cpp
 * Author: Charles Gilljam
 * 
 * Created on April 28, 2013, 6:59 PM
 */

#include "PhysObject.h"
#include "Material.h"
#include "PhysHandler.h"

PhysHandler PhysObject::default_handler{};

PhysObject::PhysObject(Parametric_Surface surface, PhysHandler handler, PointVector<> velocity):
	_material{},
	_volume{1},
	_velocity{velocity},
	_surface(surface)
{
	handler.physObjects.push_back(*this);
}

PhysObject::PhysObject(const PhysObject& /*orig*/):
	_surface(Geometry::def_param_axis_func, {0,0,0})
{
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
	return _surface.position;
}

PointVector<>& PhysObject::velocity(){
	return _velocity;
}


PointVector<>& PhysObject::acceleration(){
	return _acceleration;
}

std::vector<std::pair<PointVector<> , double>>& PhysObject::impulses(){
	return _impulses;
}

void PhysObject::addImpulse(PointVector<> a, double time){
	_impulses.push_back(std::make_pair(a,time));
}

Parametric_Surface& PhysObject::surface(){
	return _surface;
}

void PhysObject::calcVolume(){
	
}

void PhysObject::accelerate(PointVector<> a){
	_acceleration = _acceleration + a;
}


void PhysObject::collision(PhysObject& obj1,PhysObject& obj2){
	obj1._velocity = (obj1._velocity.getMagnitude()*(obj1.density()*obj1._volume-obj2.density()*obj2._volume)+2.0*obj2.density()*obj2._volume*obj2._velocity.getMagnitude())/(obj1._volume*obj1.density() + obj2._volume*obj2.density()) * obj1._velocity.reflect(2.0*obj1.position()-obj2.position()).make_unit();
	obj2._velocity = (obj2._velocity.getMagnitude()*(obj2.density()*obj2._volume-obj1.density()*obj1._volume)+2.0*obj1.density()*obj1._volume*obj1._velocity.getMagnitude())/(obj2._volume*obj2.density() + obj1._volume*obj1.density()) * obj2._velocity.reflect(2.0*obj2.position()-obj1.position()).make_unit();
}

