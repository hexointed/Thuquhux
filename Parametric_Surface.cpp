/* 
 * File:   NURBS.cpp
 * Author: elias
 * 
 * Created on April 24, 2013, 4:42 PM
 */

#include "Parametric_Surface.h"
#include <math.h>
#include "PointVector.h"
#include "GL/freeglut.h"
#include <iostream>
#include <vector>

double PI = 3.14159265358979;

Parametric_Surface::Parametric_Surface(double (*x)(double, double), double (*y)(double, double), double (*z)(double, double)):
	mesh_detail(40),
	mesh_length((mesh_detail + 2)*(mesh_detail + 1)*2)
{
	mesh_vertecies.push_back(new PointVector[mesh_length]);
	
	pfuncs[0] = x;
	pfuncs[1] = y;
	pfuncs[2] = z;
	
	this->bound_box[0] = new PointVector(0,0,0);
	this->bound_box[1] = new PointVector(0,0,0);
	
	this->position = new PointVector(0,0,0);
}

Parametric_Surface::~Parametric_Surface() {
}

void Parametric_Surface::Unite(Parametric_Surface a){
	this->mesh_vertecies.push_back(new PointVector[a.mesh_length]);
	for(int i = 0; i < a.mesh_length; i++){
		PointVector p = a.mesh_vertecies.at(a.mesh_vertecies.size()-1)[i];
		p.add(*a.position)->sub(*this->position);
		this->mesh_vertecies.at(this->mesh_vertecies.size()-1)[i].setdx(p.getdx());
		this->mesh_vertecies.at(this->mesh_vertecies.size()-1)[i].setdy(p.getdy());
		this->mesh_vertecies.at(this->mesh_vertecies.size()-1)[i].setdz(p.getdz());
	}
}

bool Parametric_Surface::is_subset_of(const Parametric_Surface& v){
	return	this->bound_box[1]->getdx() + this->position->getdx() < v.bound_box[1]->getdx() + v.position->getdx() &&
			this->bound_box[1]->getdy() + this->position->getdy() < v.bound_box[1]->getdy() + v.position->getdy() &&
			this->bound_box[1]->getdz() + this->position->getdz() < v.bound_box[1]->getdz() + v.position->getdz() &&
			
			this->bound_box[0]->getdx() + this->position->getdx() > v.bound_box[0]->getdx() + v.position->getdx() &&
			this->bound_box[0]->getdy() + this->position->getdy() > v.bound_box[0]->getdy() + v.position->getdy() &&
			this->bound_box[0]->getdz() + this->position->getdz() > v.bound_box[0]->getdz() + v.position->getdz();
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
	for(int n = 0; n < mesh_vertecies.size(); n++){
		for(int i = 0; i <= 1+mesh_detail; i++){
			for(int j = 0; j <= mesh_detail; j++){
				double t = i*(1.0/mesh_detail);
				double u = j*(1.0/mesh_detail);
				mesh_vertecies.at(0)[count].setdx(pfuncs[0](t,u));
				mesh_vertecies.at(0)[count + 1].setdx(pfuncs[0](t + 1.0/mesh_detail, u));
				bound_box[0]->setdx(pfuncs[0](t,u) < bound_box[0]->getdx() ? pfuncs[0](t,u) : bound_box[0]->getdx());
				bound_box[1]->setdx(pfuncs[0](t,u) > bound_box[1]->getdx() ? pfuncs[0](t,u) : bound_box[1]->getdx());
			
				mesh_vertecies.at(0)[count].setdy(pfuncs[1](t,u));
				mesh_vertecies.at(0)[count + 1].setdy(pfuncs[1](t + 1.0/mesh_detail, u));
				bound_box[0]->setdy(pfuncs[1](t,u) < bound_box[0]->getdy() ? pfuncs[1](t,u) : bound_box[0]->getdy());
				bound_box[1]->setdy(pfuncs[1](t,u) > bound_box[1]->getdy() ? pfuncs[1](t,u) : bound_box[1]->getdy());
			
				mesh_vertecies.at(0)[count].setdz(pfuncs[2](t,u));
				mesh_vertecies.at(0)[count + 1].setdz(pfuncs[2](t + 1.0/mesh_detail, u));
				bound_box[0]->setdz(pfuncs[2](t,u) < bound_box[0]->getdz() ? pfuncs[2](t,u) : bound_box[0]->getdz());
				bound_box[1]->setdz(pfuncs[2](t,u) > bound_box[1]->getdz() ? pfuncs[2](t,u) : bound_box[1]->getdz());
				count += 2;
			}
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