/* 
 * File:   Triangle.cpp
 * Author: elias
 * 
 * Created on May 23, 2013, 7:11 PM
 */

#include "Geometry.h"
#include "../GL/freeglut.h"
#include <iostream>

using namespace Geometry;

template<const int Sides, const int Dim>
Polygon<Sides, Dim>::Polygon(){
}

template<const int Sides, const int Dim>
Polygon<Sides, Dim>::Polygon(PointVector<Dim>* sides){
	for(int i = 0; i < Sides; i++){
		this->vertecies[i] = sides[i];
	}
}

template<const int Sides, const int Dim>
Polygon<Sides, Dim>::Polygon(const Polygon<Sides,Dim>& orig){
	for(int i = 0; i < Sides; i++){
		this->vertecies[i] = orig.vertecies[i];
	}
}

template<const int Sides, const int Dim>
Polygon<Sides, Dim>::~Polygon(){
}

Triangle::Triangle(PointVector<>* sides): Polygon<3>(sides) {
	std::cout<<vertecies[1].getdy()<<std::endl;
}

Triangle::Triangle(const Triangle& orig) {
}

Triangle::~Triangle() {
}

bool Triangle::collisionWith(Triangle& T1){
	Triangle& T2 = *this;
	//this = 2, a = 1
	
	PointVector<> n2 = PointVector<>::mul_cross(PointVector<>::sub(T2.vertecies[1], T2.vertecies[0]), PointVector<>::sub(T2.vertecies[2], T2.vertecies[0]));
	double d2 = PointVector<>::mul_dot(PointVector<>::mul(-1,n2), T2.vertecies[0]);
	
	double adv0 = PointVector<>::mul_dot(n2, T1.vertecies[0]) + d2;
	double adv1 = PointVector<>::mul_dot(n2, T1.vertecies[1]) + d2;
	double adv2 = PointVector<>::mul_dot(n2, T1.vertecies[2]) + d2;
	
	bool asign = (adv0 >= 0) ^ (adv1 < 0) && (adv0 >= 0) ^ (adv2 < 0);
	if((adv0 != 0) && (adv1 != 0) && (adv2 != 0) && asign)
		return false;
	
	PointVector<> n1 = PointVector<>::mul_cross(PointVector<>::sub(T1.vertecies[1], T1.vertecies[0]), PointVector<>::sub(T1.vertecies[2], T1.vertecies[0]));
	double d1 = PointVector<>::mul_dot(PointVector<>::mul(-1,n1), T1.vertecies[0]);
	
	double dv0 = PointVector<>::mul_dot(n1, T2.vertecies[0]) + d1;
	double dv1 = PointVector<>::mul_dot(n1, T2.vertecies[1]) + d1;
	double dv2 = PointVector<>::mul_dot(n1, T2.vertecies[2]) + d1;
	
	bool sign = (dv0 >= 0) ^ (dv1 < 0) && (dv0 >= 0) ^ (dv2 < 0);
	if(dv0 != 0 && dv1 != 0 && dv2 != 0 && sign)
		return false;
	
	if(dv0 == 0 && dv1 == 0 && dv2 == 0)
		return false;

	PointVector<> lineD = PointVector<>::mul_cross(n2, n1);
	double p0 = PointVector<>::mul_dot(lineD, vertecies[0]);
	double p1 = PointVector<>::mul_dot(lineD, vertecies[1]);
	double p2 = PointVector<>::mul_dot(lineD, vertecies[2]);
	double ap0 = PointVector<>::mul_dot(lineD, T1.vertecies[0]);
	double ap1 = PointVector<>::mul_dot(lineD, T1.vertecies[1]);
	double ap2 = PointVector<>::mul_dot(lineD, T1.vertecies[2]);
	
	double t0 = p0 + (p1 -p0)*dv0/(dv0-dv1);
	double t1 = p1 + (p2 -p1)*dv1/(dv1-dv2);
	double at0 = ap0 + (ap1 -ap0)*adv0/(adv0-adv1);
	double at1 = ap1 + (ap2 -ap1)*adv1/(adv1-adv2);
	if((t0 <= at0 && at0 <= t1) || (t0 <= at1 && at1 <= t1) )//|| (t0 >= at0 && at0 >= t1) || (t0 >= at0 && at1 >= t1))
		return true;
	
	return false;
}

bool Triangle::passesThrough(PointVector<>& max, PointVector<>& min){
	bool result = true;
	PointVector<> d[3] = {vertecies[0], vertecies[1], vertecies[2]};
	for(int i = 0; i < 3; i++){
		d[i].mul_comp(d[i]);
		
	}
	return result;
}

void Triangle::draw(){
	glTranslatef(0,0,0);
	glVertexPointer(3, GL_DOUBLE, 0, vertecies);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
}