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

double PI = 3.14159265358979;

Parametric_Surface::Parametric_Surface(double (*x)(double, double), double (*y)(double, double), double (*z)(double, double)):
	mesh_detail(80)
{
	int length = mesh_detail*mesh_detail*2*mesh_detail;
	mesh_vertecies.push_back(new PointVector[length]);
	
	pfuncs[0] = x;
	pfuncs[1] = y;
	pfuncs[2] = z;
	
	this->bound_box[0] = new PointVector(0,0,0);
	this->bound_box[1] = new PointVector(0,0,0);
	
	this->position = new PointVector(0,0,0);
}

Parametric_Surface::Parametric_Surface(const Parametric_Surface& orig) {
}

Parametric_Surface::~Parametric_Surface() {
	delete position;
	delete[] bound_box[0];
	delete[] bound_box[1];
	
	for(int i = 0; i < 3; i++){
		delete[] hq_mesh[i];
	}
}

void Parametric_Surface::Unite(Parametric_Surface a, PointVector pos){
	
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
	for(double t = 0; t <= 1 + 1.0/mesh_detail; t += 1.0/mesh_detail){
		for(double u = 0; u <= 1; u += 1.0/mesh_detail){
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

void Parametric_Surface::drawMesh(){
	for(int i = 0; i < 1; i++){
		glPushMatrix();
			glTranslatef(position->getdx(), position->getdy(), position->getdz());
			glVertexPointer(3,GL_DOUBLE,0,mesh_vertecies.at(0));
			glDrawArrays(GL_TRIANGLE_STRIP,0,mesh_detail*mesh_detail*2);
		glPopMatrix();
	}
}