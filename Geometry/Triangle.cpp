/* 
 * File:   Triangle.cpp
 * Author: Elias Forsberg
 * 
 * Created on May 23, 2013, 7:11 PM
 */

#include "Triangle.h"
#include "../GL/freeglut.h"
#include <iostream>
#include <vector>

using namespace Geometry;

Triangle& Triangle::move(const Vector<> diff){
	this->vertecies[0] += diff;
	this->vertecies[1] += diff;
	this->vertecies[2] += diff;
	return *this;
}

Triangle Triangle::operator +(const Vector<> a){
	Triangle ret = *this;
	ret.vertecies[0] += a;
	ret.vertecies[1] += a;
	ret.vertecies[2] += a;
	return ret;
}

bool Triangle::shares_side(const Triangle& with){
	int res = 0;
	for(const Vector<>& a : vertecies){
		for(const Vector<>& b : with.vertecies){
			if(&a == &b)
				++res;
		}
	}
    return res == 2;
}

bool Triangle::passesThrough(Vector<>& /*max*/, Vector<>& /*min*/){
	bool result = true;
	Vector<> d[3] = {vertecies[0], vertecies[1], vertecies[2]};
	for(int i = 0; i < 3; i++){
		d[i].mul_comp(d[i]);
		
	}
	return result;
}

std::pair<bool, Vector<>> Triangle::intersectionWith(Polygon<2> p) const{
	auto no_true = std::make_pair(false, Vector<>{});
	
	auto& q = *this;
	auto u = q.vertecies[1] - q.vertecies[0];
	auto v = q.vertecies[2] - q.vertecies[0];
	auto n = Vector<>::mul_cross(u, v);
	
	auto divisor = Vector<>::mul_dot(n, p[1]- p[0]);
	if(divisor == 0)
		return no_true;
	auto r = Vector<>::mul_dot(n, q.vertecies[0] - p[0])/divisor;
	if(r < 0 || r > 1)
		return no_true;
	
	auto pi = p[0] + r * (p[1]-p[0]);
	auto w = pi - q.vertecies[0];
	
	auto tmp = Vector<>::mul_dot(u,v);
	auto div = tmp*tmp - Vector<>::mul_dot(u,u)*Vector<>::mul_dot(v,v);
	if(div == 0)
		return no_true;
	
	auto si = (tmp * Vector<>::mul_dot(w,v) - Vector<>::mul_dot(v,v)*Vector<>::mul_dot(w,u))/div;
	if(si < 0)
		return no_true;
	auto ti = (tmp * Vector<>::mul_dot(w,u) - Vector<>::mul_dot(u,u)*Vector<>::mul_dot(w,v))/div;
	if(ti < 0 || si+ti > 1)
		return no_true;
	return std::make_pair(true, q.vertecies[0] + si*u + ti*v);
}

std::pair<bool, std::vector<Vector<>>> Triangle::intersectionWith(Triangle q) const{
	Triangle p = *this;
	std::vector<Vector<>> results;
	for(int i = 0; i < 2; i++){
		
		for(int i = 0; i < 3; i++){
			Polygon<2> line;
			line[0] = p.vertecies[i];
			line[1] = p.vertecies[(i+1)%3];
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

std::vector<Triangle> Triangle::split(Vector<> pos, Vector<> normal) const {
	std::vector<Triangle> result;
	std::vector<Vector<>> side1, side2;
	for(Vector<> p : vertecies){
		if(Vector<>::mul_dot(pos - p, normal) > 0){
			side1.push_back(p);
		}else{
			side2.push_back(p);
		}
	}
	if(side1.size()==3 || side2.size()==3){
		result.push_back(*this);
		return result;
	}
	
	std::vector<Vector<>>& big_side = side1.size() > side2.size() ? side1 : side2;
	Vector<>& small_side = side1.size() < side2.size() ? side1.front() :  side2.front();
	
	Vector<> vec1 = big_side[0] - small_side;
	Vector<> vec2 = big_side[1] - small_side;
	
	double d1 = Vector<>::mul_dot((pos - small_side), normal) /
	            Vector<>::mul_dot(vec1, normal);
	double d2 = Vector<>::mul_dot((pos - small_side), normal) /
	            Vector<>::mul_dot(vec2, normal);
	
	Vector<> p1 = small_side + d1*vec1;
	Vector<> p2 = small_side + d2*vec2;
	
	result.push_back(Triangle{big_side[0], big_side[1], p1});
	result.push_back(Triangle{big_side[1], p1, p2});
	result.push_back(Triangle{small_side , p2, p1});
	
	return result;
}

Vector<> Triangle::normal() const {
	return Vector<>::mul_cross(vertecies[1] - vertecies[0], vertecies[2] - vertecies[0]);
}

void Triangle::draw(){
	glBegin(GL_TRIANGLES);
		glVertex3dv((double*)&vertecies[0]);
		glVertex3dv((double*)&vertecies[1]);
		glVertex3dv((double*)&vertecies[2]);
	glEnd();
}
