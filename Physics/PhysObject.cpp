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

void PhysObject::create(bool addToList, Parametric_Surface surface, PhysHandler& handler, PointVector<> velocity){
	PhysObject erland(surface, velocity);
	if(addToList){
		handler.physObjects.push_back(erland);
	}

}

PhysObject& PhysObject::create_return(bool addToList, Parametric_Surface surface, PhysHandler& handler, PointVector<> velocity){
	PhysObject erland(surface, velocity);
	if(addToList){
		handler.physObjects.push_back(erland);
	}
	return handler.physObjects.back();
}

PhysObject::PhysObject(Parametric_Surface surface, PointVector<> velocity):
	_material{},
	_volume{1},
	_velocity{velocity},
	_surface(surface),
	_rotation{{1,0,0},0}
{

}

PhysObject::PhysObject(const PhysObject& orig):
	_surface(orig._surface),
	_rotation(orig._rotation)
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

PointVector<>& PhysObject::previous_position(){
	return _previous_position;
}

PointVector<>& PhysObject::acceleration(){
	return _acceleration;
}

std::pair<PointVector<>, double>& PhysObject::rotation(){
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


void PhysObject::collision(PhysObject& obj1,PhysObject& obj2, PointVector<> collide_at, PointVector<> normal){
	//double mass1 = obj1._volume*obj1.density();
	//double mass2 = obj2._volume*obj2.density();
	double mass1 = 5;
	double mass2 = 10;

	
	PointVector<> cun1 = PointVector<>::mul_cross(collide_at - obj1.position(), normal);
	PointVector<> cun2 = PointVector<>::mul_cross(collide_at - obj2.position(), normal);

	double lambda = 2.0 * (PointVector<>::mul_dot(obj1._velocity - obj2._velocity, normal) + PointVector<>::mul_dot(obj1._rotation.first*obj1._rotation.second, cun1) - PointVector<>::mul_dot(obj2._rotation.first*obj2._rotation.second, cun2)) / ((1.0/mass1) + (1.0/mass2) + PointVector<>::mul_dot(cun1,cun1) + PointVector<>::mul_dot(cun2,cun2)); 

	PointVector<> finalVel1 = (obj1._velocity - lambda/mass1 * normal);
	PointVector<> finalVel2 = (obj2._velocity + lambda/mass2 * normal);
	PointVector<> finalRotation1 = (obj1._rotation.first * obj1._rotation.second)-lambda*cun1;
	PointVector<> finalRotation2 = (obj2._rotation.first * obj2._rotation.second)+lambda*cun2;


	if(finalRotation1.getMagnitude() == 0){
		obj1._rotation.first = {1,0,0};
	}else{
		obj1._rotation.first = finalRotation1.make_unit();
	}
	obj1._rotation.second = finalRotation1.getMagnitude() * (obj1.position() - collide_at).getMagnitude()/sqrt(mass1);
	if(finalRotation2.getMagnitude() == 0){
		obj2._rotation.first = {1,0,0};
	}else{
		obj2._rotation.first = finalRotation1.make_unit();
	}
	obj2._rotation.second = finalRotation2.getMagnitude() * (obj2.position() - collide_at).getMagnitude()/sqrt(mass2);

	obj1._velocity = finalVel1;
	obj2._velocity = finalVel2;
	
}

