/*
 * File:   Geometry/Surface.cpp
 * Author: Elias Forsberg
 *
 * Created on April 24, 2013, 4:42 PM
 */

#include "Geometry.h"
#include "Surface.h"
#include <math.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using Geometry::Surface;
using Geometry::Triangle;
using Geometry::Vector;

double PI = 3.14159265358979;

Surface::Surface(Vector<> pos):
	detail{10},
	prop_upd_volume{false},
	prop_volume{0},
	prop_upd_area{false},
	prop_area{0},
	bound_box{{0,0,0},{0,0,0}},
	position(pos)
{}

void Surface::Unite(Surface a){
	Vector<> rel_pos = a.position - position;
	bound_box[0].set_min_comp(a.bound_box[0] + rel_pos);
	bound_box[1].set_max_comp(a.bound_box[1] + rel_pos);
	for(auto& v : a.mesh.vertecies()){
		v.position += rel_pos;
	}
	mesh.add(a.mesh);
}

bool Surface::is_subset_of(const Surface& v){
	Vector<> p = bound_box[1];
	Vector<> q = v.bound_box[1];
	Vector<> r = bound_box[0];
	Vector<> s = v.bound_box[0];
	
	return	p.add(position).is_min_comp(q.add(v.position)) && 
	        r.add(position).is_max_comp(s.add(v.position));
}

bool Surface::is_superset_of(const Surface& v){
	auto p = bound_box[1];
	auto q = v.bound_box[1];
	auto r = bound_box[0];
	auto s = v.bound_box[0];
	return p.add(position).is_max_comp(q.add(v.position)) &&
	       r.add(position).is_min_comp(s.add(v.position));
}

bool Surface::isIntersecting(Surface& v){
	for(Triangle tri : mesh){
		for(Triangle vtri : v.mesh){
			vtri.move(position - v.position);
			if(tri.intersectionWith(vtri).first){
				return true;
			}
		}
	}
	return false;
}

std::pair<Vector<>, Vector<>> Surface::collision_data(Surface& v){
	std::pair<Vector<>, Vector<>> result; //position, normal
	std::vector<Triangle> intersections;
	std::vector<Triangle> intersections_v;
	for(Triangle t : mesh){
		for(Triangle vt : v.mesh){
			if(t.intersectionWith(vt).first){
				intersections.push_back(t);
				intersections_v.push_back(vt);
			}
		}
	}
	for(Triangle t : intersections){
		result.first += (t[0] + t[1] + t[2])/3.0;
		result.second -= t.normal();
	}
	for(Triangle t : intersections_v){
		result.first += (t[0] + t[1] + t[2])/3.0;
		result.second += t.normal();
	}
	result.second /= double(intersections.size() + intersections_v.size());
	result.second /= double(intersections.size() + intersections_v.size());
	return result;
}

double Surface::distance_from(const Surface& v){
	return (position - v.position).magnitude();
}

bool Surface::pointIsWithin(Vector<> p){
	if(p.is_min_comp(bound_box[0]) || p.is_max_comp(bound_box[1]))
		return false;
	Vector<> min {p[0], p[1], bound_box[0][2]};
	Vector<> max {p[0], p[1], bound_box[1][2]};
	Polygon<2> clip_line;
	clip_line[0] = min;
	clip_line[1] = max;
	std::vector<Vector<>> clips;
	for(Triangle tri: mesh){
		auto tmp = tri.intersectionWith(clip_line);
		if(tmp.first)
			clips.push_back(tmp.second);
	}
	std::sort(clips.begin(), clips.end(), 
	          [](Vector<> a, Vector<> b){return a[2]<b[2];});
	bool state = false;
	for(Vector<> pos: clips){
		state = !state;
		if(pos[2] > p[2])
			return !state;
	}
	return false;
}

double Surface::volume(){
	if(prop_upd_volume){
		return prop_volume;
	}
	prop_volume = 0.0;
	Geometry::Vector<>test_pos = bound_box[0];
	Geometry::Vector<>step = (bound_box[1] - bound_box[0])/double(detail);
	double unit_volume = step[0] * step[1] * step[2];
	for(; test_pos[0] < bound_box[1][0]; test_pos[0] += step[0]){
		for(; test_pos[1] < bound_box[1][1]; test_pos[1] += step[1]){
			for(; test_pos[2] < bound_box[1][2]; test_pos[2] += step[2]){
				if(pointIsWithin(test_pos)){
					prop_volume += unit_volume;
				}
			}
		}
	}
	prop_upd_volume = true;
	return prop_volume;
};

double Surface::area(){
	if(prop_upd_area){
		return prop_area;
	}
	prop_area = 0.0;
	for(Triangle t : mesh){
		prop_area += t.area();
	}
	prop_upd_area = true;
	return prop_area;
}

Vector<> Geometry::def_param_axis_func(Vector<2> params){
	params = params.mul(2*PI);
	Vector<> arr = {cos(params[0])*(1 + 0.25*cos(params[1])),
	                sin(params[0])*(1 + 0.25*cos(params[1])),
	                0.25*sin(params[1])};
	return arr;
}

void Surface::rotate(Vector<> axis, double angle){
	bound_box[0] = bound_box[1] = position;
	for(auto& p: mesh.vertecies()){
		p.position = p.position.rotate(angle, axis);
		bound_box[0].set_min_comp(p.position);
		bound_box[1].set_max_comp(p.position);
	}
}
