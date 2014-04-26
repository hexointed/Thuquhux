/*
 * File: ScatterProp.cpp
 * Author: Elias Forsberg
 *
 * Created on April 24, 2014, 2:05 PM
 */

#include "ScatterProp.h"

using namespace Terrain;
using Scatters::Trees::Oak;

void ScatterProp::set_depth(int d){
	depth = d;
}

void ScatterProp::set_parent(Node& n){
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
	distrib(0,0.5)
{}

Geometry::Vector<> Acacia::position(){
	auto pos = parent.position + Geometry::Vector<>{distrib()*0.1,
	                                                0.4 + distrib()*0.2,
	                                                distrib()*0.1};
	/* All branches must spring away from eachother, to prevent self-intersections */
	auto self_avoid = [&pos](Geometry::Vector<>& position, double& weight) -> void {
		double dist = (pos - position).magnitude();
		pos = pos + (pos - position) / (dist * dist);
	};
	base->forall(self_avoid);
	return pos;
}

double Acacia::weight(){
	return 1 / sqrt(depth);
}

bool Acacia::is_end(){
	return depth > 15;
}

bool Acacia::split(){
	return !depth%3;
}
