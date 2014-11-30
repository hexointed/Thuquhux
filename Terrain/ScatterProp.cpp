/*
 * File: ScatterProp.cpp
 * Author: Elias Forsberg
 *
 * Created on April 24, 2014, 2:05 PM
 */

#include "ScatterProp.h"
#include "../Utility/Random.h"

using namespace Terrain;
using Scatters::Trees::Acacia;
using Geometry::Vector;

namespace {
	Vector<> rotate_point(Vector<> point, Vector<> axis, double angle){
		axis.make_unit();
		const Vector<> r1{cos(angle) + axis.getdx()*axis.getdx()*(1 - cos(angle)),
		          axis.getdx()*axis.getdy()*(1 - cos(angle)) - axis.getdz()*sin(angle),
		          axis.getdx()*axis.getdz()*(1 - cos(angle)) + axis.getdy()*sin(angle)};
		const Vector<> r2{axis.getdy()*axis.getdx()*(1 - cos(angle)) + axis.getdz()*sin(angle),
		          cos(angle) + axis.getdy()*axis.getdy()*(1 - cos(angle)),
		          axis.getdy()*axis.getdz()*(1 - cos(angle)) - axis.getdx()*sin(angle)};
		const Vector<> r3{axis.getdz()*axis.getdx()*(1 - cos(angle)) - axis.getdy()*sin(angle),
		                 axis.getdz()*axis.getdy()*(1 - cos(angle)) + axis.getdx()*sin(angle),
		                 cos(angle) + axis.getdz()*axis.getdz()*(1 - cos(angle))};
		const Vector<> tmp = point;
		return {Vector<>::mul_dot(r1, tmp),
		        Vector<>::mul_dot(r2, tmp),
		        Vector<>::mul_dot(r3, tmp)};
	}
}

namespace {
	Random rd;
}

void ScatterProp::set_depth(int d){
	depth = d;
}

void ScatterProp::set_parent(ScatterTree::Node& n){
	if(parent == nullptr){
		base = &n;
	}
	parent = &n;
}

/*
 * Derived classes below.
 */

Acacia::Acacia():
	ScatterProp(),
	distrib(0, 0.5)
{}

Geometry::Vector<> Acacia::position(){
	Geometry::Vector<> up{0,1,0};
	if(!parent){
		return Geometry::Vector<>{0, 0, 0};
	}
	try{
		Geometry::Vector<> prev_fwd = parent->position -  parent->up().position;
		auto pos = parent->position +
			rd.normal(1.0, 0.05) * rotate_point(prev_fwd,
			{rd.normal(0.0,0.3),
			 rd.normal(0.0,0.3),
			 rd.normal(0.0,0.3)},
			rd.normal(0.0, 0.1) ) ;
		if(depth > 6){
			pos -= 0.01 * up / weight();
		}
		return pos;
	} catch (...){
		return 0.3*up;
	}
}

double Acacia::weight(){
	return 1 / sqrt(depth);
}

bool Acacia::is_end(){
	return depth > 15;
}

bool Acacia::split(){
	return !(depth%3);
}
