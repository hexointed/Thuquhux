/* 
 * File:   Paramertic_Surface.cpp
 * Author: Elias Forsberg
 * 
 * Created on April 24, 2013, 4:42 PM
 */
#include "../PointVector.h"
#include "Parametric_Surface.h"
#include <math.h>

#include "GL/freeglut.h"
#include <iostream>
#include <vector>

using Geometry::Parametric_Surface;

double PI = 3.14159265358979;

Parametric_Surface::Parametric_Surface():
	mesh_detail(400),
	mesh_length((mesh_detail + 2)*(mesh_detail + 1)*2)
{
	mesh_vertecies.push_back(new PointVector<>[mesh_length]);
	
	this->bound_box[0] = new PointVector<>(0,0,0);
	this->bound_box[1] = new PointVector<>(0,0,0);
	
	this->position = new PointVector<>(0,0,0);
}

Parametric_Surface::~Parametric_Surface() {
}

void Parametric_Surface::Unite(Parametric_Surface a){
	this->mesh_vertecies.push_back(new PointVector<>[a.mesh_length]);
	for(int i = 0; i < a.mesh_length; i++){
		PointVector<> p = a.mesh_vertecies.at(a.mesh_vertecies.size()-1)[i];
		p.add(*a.position).sub(*this->position);
		this->mesh_vertecies.at(this->mesh_vertecies.size()-1)[i] = p;
		bound_box[0]->set_min_comp(p);
		bound_box[1]->set_max_comp(p);
	}
}

bool Parametric_Surface::is_subset_of(const Parametric_Surface& v){
	PointVector<> p = *bound_box[1];
	PointVector<> q = *v.bound_box[1];
	PointVector<> r = *bound_box[0];
	PointVector<> s = *v.bound_box[0];
	
	return	p.add(*position).is_min_comp(q.add(*v.position)) && r.add(*position).is_max_comp(s.add(*v.position));
}

bool Parametric_Surface::is_superset_of(const Parametric_Surface& v){
	return	this->bound_box[1]->getdx() + this->position->getdx() > v.bound_box[1]->getdx() + v.position->getdx() &&
			this->bound_box[1]->getdy() + this->position->getdy() > v.bound_box[1]->getdy() + v.position->getdy() &&
			this->bound_box[1]->getdz() + this->position->getdz() > v.bound_box[1]->getdz() + v.position->getdz() &&
			
			this->bound_box[0]->getdx() + this->position->getdx() < v.bound_box[0]->getdx() + v.position->getdx() &&
			this->bound_box[0]->getdy() + this->position->getdy() < v.bound_box[0]->getdy() + v.position->getdy() &&
			this->bound_box[0]->getdz() + this->position->getdz() < v.bound_box[0]->getdz() + v.position->getdz();
}

bool Parametric_Surface::isIntersecting(const Parametric_Surface& v){
	return	this->bound_box[1]->getdx() + this->position->getdx() > v.bound_box[0]->getdx() + v.position->getdx() &&
			this->bound_box[1]->getdy() + this->position->getdy() > v.bound_box[0]->getdy() + v.position->getdy() &&
			this->bound_box[1]->getdz() + this->position->getdz() > v.bound_box[0]->getdz() + v.position->getdz() &&
			
			this->bound_box[0]->getdx() + this->position->getdx() < v.bound_box[1]->getdx() + v.position->getdx() &&
			this->bound_box[0]->getdy() + this->position->getdy() < v.bound_box[1]->getdy() + v.position->getdy() &&
			this->bound_box[0]->getdz() + this->position->getdz() < v.bound_box[1]->getdz() + v.position->getdz();
}

PointVector<> Geometry::def_param_axis_func(PointVector<> params){
	params.mul(2*PI);
	double arr[3] = {cos(params.getdx())*(1 + 0.25*cos(params.getdy())), sin(params.getdx())*(1 + 0.25*cos(params.getdy())), 0.25*sin(params.getdy())};
	return PointVector<>(arr);
}


void Parametric_Surface::calculate_mesh(){
	int count = 0;
	for(double t = 0; t <= 1 + 1.0/mesh_detail; t += 1.0/mesh_detail){
		for(double u = 0; u <= 1; u += 1.0/mesh_detail){
			PointVector<> params(t,u,0);
			PointVector<> dparams(t + 1.0/mesh_detail,u,0);
			PointVector<> p(Geometry::def_param_axis_func(params));
			PointVector<> dp(Geometry::def_param_axis_func(dparams));
			mesh_vertecies.at(0)[count] = p;
			mesh_vertecies.at(0)[count +1] = dp;
			bound_box[0]->set_min_comp(p);
			bound_box[1]->set_max_comp(p);
			count += 2;
		}
	}
}

void Parametric_Surface::drawMesh(){
	glPushMatrix();
	glTranslatef(position->getdx(), position->getdy(), position->getdz());
	for(int i = 0; i < mesh_vertecies.size(); i++){
		glVertexPointer(3,GL_DOUBLE,0,mesh_vertecies.at(i));
		glDrawArrays(GL_TRIANGLE_STRIP,0,mesh_length);
	}
	glPopMatrix();
}
