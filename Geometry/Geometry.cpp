/* 
 * File:   Triangle.cpp
 * Author: Elias Forsberg
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

Triangle::Triangle(PointVector<>* sides){
	vertecies[0] = sides[0];
	vertecies[1] = sides[1];
	vertecies[2] = sides[2];
}

Triangle::Triangle(PointVector<> a, PointVector<> b, PointVector<> c):
	vertecies{a,b,c}
{}

Triangle::~Triangle(){}

Triangle& Triangle::move(const PointVector<> diff){
	this->vertecies[0] += diff;
	this->vertecies[1] += diff;
	this->vertecies[2] += diff;
	return *this;
}

Triangle Triangle::operator +(const PointVector<> a){
	Triangle ret = *this;
	ret.vertecies[0] += a;
	ret.vertecies[1] += a;
	ret.vertecies[2] += a;
	return ret;
}

PointVector<>& Triangle::operator [](const int vertex){
	return vertecies[vertex];
}

bool Triangle::shares_side(const Triangle& with){
	int res = 0;
	for(const PointVector<>& a : vertecies){
		for(const PointVector<>& b : with.vertecies){
			if(&a == &b)
				++res;
		}
	}
    return res == 2;
}

bool Triangle::passesThrough(PointVector<>& /*max*/, PointVector<>& /*min*/){
	bool result = true;
	PointVector<> d[3] = {vertecies[0], vertecies[1], vertecies[2]};
	for(int i = 0; i < 3; i++){
		d[i].mul_comp(d[i]);
		
	}
	return result;
}

std::pair<bool, PointVector<>> Triangle::intersectionWith(Polygon<2> p){
	auto no_true = std::make_pair(false, PointVector<>{});
	
	auto& q = *this;
	auto u = q.vertecies[1] - q.vertecies[0];
	auto v = q.vertecies[2] - q.vertecies[0];
	auto n = PointVector<>::mul_cross(u, v);
	
	auto divisor = PointVector<>::mul_dot(n, p.vertecies[1]- p.vertecies[0]);
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

std::pair<bool, std::vector<PointVector<>>> Triangle::intersectionWith(Triangle& q){
	Triangle& p = *this;
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
	std::swap(p,q);
	return std::make_pair(false,results);
}

std::vector<Triangle> Triangle::split(PointVector<> pos, PointVector<> normal) const {
	std::vector<Triangle> result;
	std::vector<PointVector<>> side1, side2;
	for(PointVector<> p : vertecies){
		if(PointVector<>::mul_dot(p, normal) > 0){
			side1.push_back(p);
		}else{
			side2.push_back(p);
		}
	}
	if(side1.size()==3 || side2.size()==3){
		result.push_back(*this);
		return result;
	}
	
	std::vector<PointVector<>>& big_side = side1.size() > side2.size() ? side1 : side2;
	PointVector<>& small_side = side1.size() < side2.size() ? side1.front() :  side2.front();
	
	PointVector<> vec1 = big_side[0] - small_side;
	PointVector<> vec2 = big_side[1] - small_side;
	
	double d1 = PointVector<>::mul_dot((pos - small_side), normal) /
	            PointVector<>::mul_dot(vec1, normal);
	double d2 = PointVector<>::mul_dot((pos - small_side), normal) /
	            PointVector<>::mul_dot(vec2, normal);
	
	PointVector<> p1 = small_side + d1*vec1;
	PointVector<> p2 = small_side + d2*vec2;
	
	if(side1.size() > side2.size()){
		result.push_back(Triangle{side1.back(), side1.front(), p1});
		result.push_back(Triangle{side1.back(), side1.front(), p2});
		result.push_back(Triangle{side2.back(), p1, p2});
	}else{
		result.push_back(Triangle{side2.back(), side2.front(), p1});
		result.push_back(Triangle{side2.back(), side2.front(), p2});
		result.push_back(Triangle{side1.back(), p1, p2});
	}
	return result;
}

PointVector<> Triangle::normal() const {
	return PointVector<>::mul_cross(vertecies[1] - vertecies[0], vertecies[2] - vertecies[0]);
}

void Triangle::draw(){
	//glTranslatef(0,0,0);
	glBegin(GL_TRIANGLES);
		glVertex3dv((double*)&vertecies[0]);
		glVertex3dv((double*)&vertecies[1]);
		glVertex3dv((double*)&vertecies[2]);
	glEnd();
}
