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
	parent = &n;
}

Oak::Oak():
	depth(0),
	parent(nullptr)
{}

Geometry::Vector<> Oak::position(){
	return parent.position + Geometry::Vector<>{0,1,0};
}

double Oak::weight(){
	return 1;
}

bool Oak::is_end(){
	return depth > 5;
}

bool Oak::split(){
	return true;
}
