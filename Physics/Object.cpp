/* 
 * File:   Physics/Object.cpp
 * Author: Charles Gilljam
 * 
 * Created on April 28, 2013, 6:59 PM
 */

#include "Object.h"
#include "Material.h"
#include "PhysHandler.h"
#include <iostream>

PhysHandler Physics::Object::default_handler{};

void Physics::Object::create(bool addToList, Parametric_Surface surface, PhysHandler& handler, Geometry::Vector<> velocity){
	Physics::Object erland(surface, velocity);
	if(addToList){
		handler.physObjects.push_back(erland);
	}

}

Physics::Object& Physics::Object::create_return(bool addToList, Parametric_Surface surface, PhysHandler& handler, Geometry::Vector<> velocity){
	Physics::Object erland(surface, velocity);
	if(addToList){
		handler.physObjects.push_back(erland);
	}
	return handler.physObjects.back();
}

Physics::Object::Object(Parametric_Surface surface, Geometry::Vector<> velocity):
	Parametric_Surface(surface),
	_material{},
	_volume{1},
	_velocity{velocity},
	_rotation{{1,0,0},0}
{

}

double& Physics::Object::density(){
	return _material.density();
}

Material& Physics::Object::material(){
	return _material;
}

Geometry::Vector<>& Physics::Object::velocity(){
	return _velocity;
}

Geometry::Vector<>& Physics::Object::previous_position(){
	return _previous_position;
}

Geometry::Vector<>& Physics::Object::acceleration(){
	return _acceleration;
}

std::pair<Geometry::Vector<>, double>& Physics::Object::rotation(){
	return _rotation;
}

std::vector<std::pair<Geometry::Vector<> , double>>& Physics::Object::impulses(){
	return _impulses;
}

void Physics::Object::addImpulse(Geometry::Vector<> a, double time){
	_impulses.push_back(std::make_pair(a,time));
}

void Physics::Object::calcVolume(){
	
}

void Physics::Object::accelerate(Geometry::Vector<> a){
	_acceleration = _acceleration + a;
}

void Physics::Object::collision(Physics::Object& obj1,Physics::Object& obj2, Geometry::Vector<> collide_at, Geometry::Vector<> normal){
	//double mass1 = obj1._volume*obj1.density();
	//double mass2 = obj2._volume*obj2.density();
	double mass1 = 5;
	double mass2 = 10;

	
	Geometry::Vector<> cun1 = Geometry::Vector<>::mul_cross(collide_at - obj1.position, normal);
	Geometry::Vector<> cun2 = Geometry::Vector<>::mul_cross(collide_at - obj2.position, normal);

	double lambda = 2.0 * (Geometry::Vector<>::mul_dot(obj1._velocity - obj2._velocity, normal) + Geometry::Vector<>::mul_dot(obj1._rotation.first*obj1._rotation.second, cun1) - Geometry::Vector<>::mul_dot(obj2._rotation.first*obj2._rotation.second, cun2)) / ((1.0/mass1) + (1.0/mass2) + Geometry::Vector<>::mul_dot(cun1,cun1) + Geometry::Vector<>::mul_dot(cun2,cun2)); 

	Geometry::Vector<> finalVel1 = (obj1._velocity - lambda/mass1 * normal);
	Geometry::Vector<> finalVel2 = (obj2._velocity + lambda/mass2 * normal);
	Geometry::Vector<> finalRotation1 = (obj1._rotation.first * obj1._rotation.second)-lambda*cun1;
	Geometry::Vector<> finalRotation2 = (obj2._rotation.first * obj2._rotation.second)+lambda*cun2;


	if(finalRotation1.getMagnitude() == 0){
		obj1._rotation.first = {1,0,0};
	}else{
		obj1._rotation.first = finalRotation1.make_unit();
	}
	obj1._rotation.second = finalRotation1.getMagnitude() * (obj1.position - collide_at).getMagnitude()/sqrt(mass1);
	if(finalRotation2.getMagnitude() == 0){
		obj2._rotation.first = {1,0,0};
	}else{
		obj2._rotation.first = finalRotation1.make_unit();
	}
	obj2._rotation.second = finalRotation2.getMagnitude() * (obj2.position - collide_at).getMagnitude()/sqrt(mass2);

	obj1._velocity = finalVel1 * (obj1.position - collide_at).getMagnitude()/sqrt(mass1);
	obj2._velocity = finalVel2 * (obj1.position - collide_at).getMagnitude()/sqrt(mass1);
	
}
