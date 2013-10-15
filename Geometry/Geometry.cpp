/* 
 * File:   Triangle.cpp
 * Author: elias
 * 
 * Created on May 23, 2013, 7:11 PM
 */

#include "Geometry.h"
#include "../GL/freeglut.h"
#include <iostream>
#include <vector>

using namespace Geometry;

template<const int Sides, const int Dim>
Polygon<Sides, Dim>::Polygon(PointVector<Dim>* sides){
	for(int i = 0; i < Sides; i++){
		this->vertecies[i] = sides[i];
	}
}

Triangle::Triangle(PointVector<>* sides) {
	for(int i = 0; i < 3; i++){
		this->vertecies[i] = sides[i];
	}
}

Triangle::Triangle(PointVector<> a, PointVector<> b, PointVector<> c):
vertecies{a,b,c}
{}

std::pair<bool, PointVector<>> Triangle::intersectionWith(Polygon<2> p){
	auto no_true = std::make_pair(false, PointVector<>{});
	
	auto q = *this;
	auto u = q.vertecies[1] - q.vertecies[0];
	auto v = q.vertecies[2] - q.vertecies[0];
	auto n = PointVector<>::mul_cross(u, v);
	
	auto divisor = PointVector<>::mul_dot(n, p.vertecies[1]-p.vertecies[0]);
	if(divisor == 0)
		return no_true;
	auto r = PointVector<>::mul_dot(n, q.vertecies[0] - p.vertecies[0])/divisor;
	if(r < 0 || r > 1)
		return no_true;
	
	auto pi = p.vertecies[0] + r * (p.vertecies[1]-p.vertecies[0]);
	auto w = pi - q.vertecies[0];
	
	auto tmp = PointVector<>::mul_dot(u,v);
	auto div = tmp*tmp - PointVector<>::mul_dot(u,u)*PointVector<>::mul_dot(v,v);
	if(div == 0)
		return no_true;
	
	auto si = (tmp * PointVector<>::mul_dot(w,v) - PointVector<>::mul_dot(v,v)*PointVector<>::mul_dot(w,u))/div;
	if(si < 0)
		return no_true;
	auto ti = (tmp * PointVector<>::mul_dot(w,u) - PointVector<>::mul_dot(u,u)*PointVector<>::mul_dot(w,v))/div;
	if(ti < 0 || si+ti > 1)
		return no_true;
	return std::make_pair(true, q.vertecies[0] + si*u + ti*v);
}

std::pair<bool, std::vector<PointVector<>>> Triangle::intersectionWith(Triangle q){
	Triangle p = *this;
	std::vector<PointVector<>> results;
	for(int i = 0; i < 2; i++){
		
		for(int i = 0; i < 3; i++){
			Polygon<2> line;
			line.vertecies[0] = p.vertecies[i];
			line.vertecies[1] = p.vertecies[(i+1)%3];
			auto res = q.intersectionWith(line);
			
			if(!res.first)
				continue;
			
			results.push_back(res.second);
			if(results.size() == 2)
				return std::make_pair(true, results);
		}
		std::swap(p,q);
	}
	return std::make_pair(false,results);
}

bool Triangle::passesThrough(PointVector<>& /*max*/, PointVector<>& /*min*/){
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
