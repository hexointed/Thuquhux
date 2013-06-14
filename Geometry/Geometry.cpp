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
/*
template<const int Sides, const int Dim>
Polygon<Sides, Dim>::Polygon(const Polygon<Sides,Dim>& orig){
	for(int i = 0; i < Sides; i++){
		this->vertecies[i] = orig.vertecies[i];
	}
}*/

template<const int Sides, const int Dim>
Polygon<Sides, Dim>::~Polygon(){
}

Triangle::Triangle(PointVector<>* sides): Polygon<3>(sides) {
	std::cout<<vertecies[1].getdy()<<std::endl;
}

//Triangle::Triangle(const Triangle& orig) {
//}

Triangle::~Triangle() {
}

bool Triangle::collisionWith(Triangle& a){
	return this->coll(a) || a.coll(*this);
}

bool Triangle::coll(Triangle& q){
	auto u = q.vertecies[1] - q.vertecies[0];
	auto v = q.vertecies[2] - q.vertecies[0];
	auto n = PointVector<>::mul_cross(u, v);
	for(int i = 0; i < 3; i++){
		auto p0 = this->vertecies[i];
		auto p1 = this->vertecies[(i+1)%3];
		
		auto divisor = PointVector<>::mul_dot(n, p1-p0);
		if(divisor == 0)
			continue;
		auto r = PointVector<>::mul_dot(n, q.vertecies[0] - p0)/divisor;
		if(r < 0 || r > 1)
			continue;
		
		auto pi = p0 + r * (p1-p0);
		auto w = pi - q.vertecies[0];
		
		auto tmp = PointVector<>::mul_dot(u,v);
		auto div = tmp*tmp - PointVector<>::mul_dot(u,u)*PointVector<>::mul_dot(v,v);
		if(div == 0)
			continue;
		
		auto si = (tmp * PointVector<>::mul_dot(w,v) - PointVector<>::mul_dot(v,v)*PointVector<>::mul_dot(w,u))/div;
		if(si < 0)
			continue;
		auto ti = (tmp * PointVector<>::mul_dot(w,u) - PointVector<>::mul_dot(u,u)*PointVector<>::mul_dot(w,v))/div;
		if(ti < 0 || si+ti > 1)
			continue;
		return true;
	}
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