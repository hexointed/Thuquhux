/* 
 * File:   PhysObject.cpp
 * Author: Charles Gilljam
 * 
 * Created on April 28, 2013, 6:59 PM
 */

#include "PhysObject.h"
#include "Material.h"
#include "PhysHandler.h"
#include <iostream>

PhysHandler PhysObject::default_handler{};

void PhysObject::create(Parametric_Surface surface, PhysHandler& handler, PointVector<> velocity){
	PhysObject erland(surface, handler, velocity);
	handler.physObjects.push_back(erland);

}

PhysObject::PhysObject(Parametric_Surface surface, PhysHandler handler, PointVector<> velocity):
	_material{},
	_volume{1},
	_velocity{velocity},
	_surface(surface)
{

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

std::pair<PointVector<>, double> PhysObject::rotation(){
	return _rotation;
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


void PhysObject::collision(PhysObject& obj1,PhysObject& obj2, PointVector<> collide_at){
	//double mass1 = obj1._volume*obj1.density();
	//double mass2 = obj2._volume*obj2.density();
	PointVector<> init1_velocity = obj1._velocity;

	double mass1 = 2;
	double mass2 = 2;
	obj2._velocity = PointVector<>{0,0.1,0};	
	std::cout << mass1 << ", " << mass2 << std::endl;

	obj1._velocity = (obj1._velocity.getMagnitude()*(mass1-mass2)+2.0*mass2*obj2._velocity.getMagnitude())/(mass1 + mass2) * obj1._velocity.reflect(2.0*obj1.position()-obj2.position()).make_unit();
	obj2._velocity = (obj2._velocity.getMagnitude()*(mass2-mass1)+2.0*mass1*init1_velocity.getMagnitude())/(mass2 + mass1) * obj2._velocity.reflect(2.0*obj2.position()-obj1.position()).make_unit();
	std::cout << obj1._velocity.getdx() << ", " << obj1._velocity.getdy() << ", " << obj1._velocity.getdz() << std::endl;
	std::cout << obj2._velocity.getdx() << ", " << obj2._velocity.getdy() << ", " << obj2._velocity.getdz() << std::endl;
	/*
	obj1._rotation.first = (PointVector<>::mul_cross(obj1._velocity, obj1.position() - collide_at).make_unit() + obj1._rotation.first.make_unit()).make_unit();
	obj1._rotation.second = (obj1.position() - collide_at).getMagnitude() - obj1._rotation.second;
	obj2._rotation.first = (PointVector<>::mul_cross(obj2._velocity, obj2.position() - collide_at).make_unit() + obj2._rotation.first.make_unit()).make_unit();
	obj2._rotation.second = (obj2.position() - collide_at).getMagnitude() - obj2._rotation.second;
	*/
}

