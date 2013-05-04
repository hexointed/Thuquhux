/* 
 * File:   NURBS.cpp
 * Author: elias
 * 
 * Created on April 24, 2013, 4:42 PM
 */

#include "NURBSSEV.h"
#include <math.h>
#include "PointVector.h"
#include "GL/freeglut.h"
#include <iostream>

double PI = 3.14159265358979;

NURBSSEV::NURBSSEV(double (*x)(double, double), double (*y)(double, double), double (*z)(double, double)):
	mesh_detail(80)
{
	int length = mesh_detail*mesh_detail*2;
	this->mesh_vertecies = new double[length][3];
	
	pfuncs[0] = x;
	pfuncs[1] = y;
	pfuncs[2] = z;
}

NURBSSEV::NURBSSEV(const NURBSSEV& orig) {
}

NURBSSEV::~NURBSSEV() {
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

void NURBSSEV::calculate_mesh(){
	int count = 0;
	for(double t = 0; t <= 1; t += 1.0/mesh_detail){
		for(double u = 0; u <= 1; u += 1.0/mesh_detail){
			for(int i = 0; i < 3; i++){
				mesh_vertecies[count][i] = pfuncs[i](t,u);
				mesh_vertecies[count + 1][i] = pfuncs[i](t + 1.0/mesh_detail, u);
				//Calculate bounding box
			}
			count += 2;
		}
	}
	std::cout<<count<<std::endl;
}

void NURBSSEV::drawMesh(){
	for(int i = 0; i < 1; i++){
		glVertexPointer(3,GL_DOUBLE,0,mesh_vertecies);
		glDrawArrays(GL_POINTS,0,mesh_detail*mesh_detail*2);
	}
}