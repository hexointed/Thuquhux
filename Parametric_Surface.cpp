/* 
 * File:   NURBS.cpp
 * Author: elias
 * 
 * Created on April 24, 2013, 4:42 PM
 */
#include "PointVector.h"
#include "Parametric_Surface.h"
#include <math.h>

#include "GL/freeglut.h"
#include <iostream>
#include <vector>

double PI = 3.14159265358979;

Parametric_Surface::Parametric_Surface(double (*x)(double, double), double (*y)(double, double), double (*z)(double, double)):
	mesh_detail(400),
	mesh_length((mesh_detail + 2)*(mesh_detail + 1)*2)
{
	mesh_vertecies.push_back(new PointVector<>[mesh_length]);
	
	pfuncs[0] = x;
	pfuncs[1] = y;
	pfuncs[2] = z;
	
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
		p.add(*a.position)->sub(*this->position);
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
	
	return	p.add(*position)->is_min_comp(*q.add(*v.position)) && r.add(*position)->is_max_comp(*s.add(*v.position));
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

double def_param_axis_func_x(double t, double u){
	return cos(t*2*PI)*(1 + 0.25*cos(u*2*PI));
}

double def_param_axis_func_y(double t, double u){
	return sin(t*2*PI)*(1 + 0.25*cos(u*2*PI));
}

double def_param_axis_func_z(double t, double u){
	return 0.25*sin(u*2*PI);
}

void Parametric_Surface::calculate_mesh(){
	int count = 0;
	for(double t = 0; t <= 1 + 1.0/mesh_detail; t += 1.0/mesh_detail){
		for(double u = 0; u <= 1; u += 1.0/mesh_detail){
			PointVector<> p(pfuncs[0](t,u), pfuncs[1](t,u), pfuncs[2](t,u));
			PointVector<> dp(pfuncs[0](t + 1.0/mesh_detail,u), pfuncs[1](t + 1.0/mesh_detail,u), pfuncs[2](t + 1.0/mesh_detail,u));
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
