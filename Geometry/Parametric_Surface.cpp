/* 
 * File:   Paramertic_Surface.cpp
 * Author: Elias Forsberg
 * 
 * Created on April 24, 2013, 4:42 PM
 */
#include "PointVector.h"
#include "Parametric_Surface.h"
#include "Geometry.h"
#include <math.h>

#include "GL/freeglut.h"
#include <iostream>
#include <vector>
#include <algorithm>

using Geometry::Parametric_Surface;

double PI = 3.14159265358979;

Parametric_Surface::~Parametric_Surface() {
}

void Parametric_Surface::Unite(Parametric_Surface a){
	PointVector<> rel_pos = a.position - position;
	bound_box[0].set_min_comp(a.bound_box[0] + rel_pos);
	bound_box[1].set_max_comp(a.bound_box[1] + rel_pos);
	for(Triangle tri: a.mesh_vertecies){
		mesh_vertecies.push_back(Triangle{tri.vertecies[0] + rel_pos, tri.vertecies[1] + rel_pos, tri.vertecies[2] + rel_pos});
	}
}

bool Parametric_Surface::is_subset_of(const Parametric_Surface& v){
	PointVector<> p = bound_box[1];
	PointVector<> q = v.bound_box[1];
	PointVector<> r = bound_box[0];
	PointVector<> s = v.bound_box[0];
	
	return	p.add(position).is_min_comp(q.add(v.position)) && r.add(position).is_max_comp(s.add(v.position));
}

bool Parametric_Surface::is_superset_of(const Parametric_Surface& v){
	return	this->bound_box[1].getdx() + this->position.getdx() > v.bound_box[1].getdx() + v.position.getdx() &&
			this->bound_box[1].getdy() + this->position.getdy() > v.bound_box[1].getdy() + v.position.getdy() &&
			this->bound_box[1].getdz() + this->position.getdz() > v.bound_box[1].getdz() + v.position.getdz() &&
			
			this->bound_box[0].getdx() + this->position.getdx() < v.bound_box[0].getdx() + v.position.getdx() &&
			this->bound_box[0].getdy() + this->position.getdy() < v.bound_box[0].getdy() + v.position.getdy() &&
			this->bound_box[0].getdz() + this->position.getdz() < v.bound_box[0].getdz() + v.position.getdz();
}

bool Parametric_Surface::isIntersecting(const Parametric_Surface& v){
	return	this->bound_box[1].getdx() + this->position.getdx() > v.bound_box[0].getdx() + v.position.getdx() &&
			this->bound_box[1].getdy() + this->position.getdy() > v.bound_box[0].getdy() + v.position.getdy() &&
			this->bound_box[1].getdz() + this->position.getdz() > v.bound_box[0].getdz() + v.position.getdz() &&
			
			this->bound_box[0].getdx() + this->position.getdx() < v.bound_box[1].getdx() + v.position.getdx() &&
			this->bound_box[0].getdy() + this->position.getdy() < v.bound_box[1].getdy() + v.position.getdy() &&
			this->bound_box[0].getdz() + this->position.getdz() < v.bound_box[1].getdz() + v.position.getdz();
}

bool Parametric_Surface::pointIsWithin(PointVector<> p){
	if(p.is_min_comp(bound_box[0]) || p.is_max_comp(bound_box[1]))
		return false;
	PointVector<> min {p.getdx(), p.getdy(), bound_box[0].getdz()};
	PointVector<> max {p.getdx(), p.getdy(), bound_box[1].getdz()};
	Polygon<2> clip_line;
	clip_line.vertecies[0] = min;
	clip_line.vertecies[1] = max;
	std::vector<PointVector<>> clips;
	for(Triangle tri: mesh_vertecies){
		auto tmp = tri.intersectionWith(clip_line);
		if(tmp.first)
			clips.push_back(tmp.second);
	}
	std::sort(clips.begin(), clips.end(), [](PointVector<> a, PointVector<> b){return a.getdz()<b.getdz();});
	bool state = false;
	for(PointVector<> pos: clips){
		state = !state;
		if(pos.getdz() > p.getdz())
			return !state;
	}
	return false;
}

PointVector<> Geometry::def_param_axis_func(PointVector<2> params){
	params.mul(2*PI);
	double arr[3] = {cos(params.getdx())*(1 + 0.25*cos(params.getdy())), sin(params.getdx())*(1 + 0.25*cos(params.getdy())), 0.25*sin(params.getdy())};
	return PointVector<>(arr);
}

void Parametric_Surface::drawMesh(){
	glPushMatrix();
	glTranslatef(position.getdx(), position.getdy(), position.getdz());
	for(Triangle tri: mesh_vertecies){
		tri.draw();
	}
	glPopMatrix();
}
