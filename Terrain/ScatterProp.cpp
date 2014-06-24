/*
 * File: ScatterProp.cpp
 * Author: Elias Forsberg
 *
 * Created on April 24, 2014, 2:05 PM
 */

#include "ScatterProp.h"

using namespace Terrain;
using Scatters::Trees::Acacia;

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

namespace{
	double ran(){
		return (rand()%2000 - 1000)/double(1000);
	}
}

Geometry::Vector<> Acacia::position(){
	Geometry::Vector<> up{0,1,0};
	if(!parent){
		return Geometry::Vector<>{0, 0, 0};
	}
	auto pos = parent->position + Geometry::Vector<>{ran()*0.1,
	                                                0.4 + ran()*0.2,
	                                                ran()*0.1};
	pos -= 0.1 * up / weight();
	/* All branches must spring away from eachother, to prevent self-intersections */
	auto self_avoid = [&pos](Geometry::Vector<>& position, double& /*weight*/) -> void {
		double dist = (pos - position).magnitude();
		pos = (pos + (pos - position) / (dist * dist)).make_unit() * pos.magnitude();
	};
	base->foreach(self_avoid);
	return pos;
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
