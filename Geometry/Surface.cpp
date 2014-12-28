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
	position{pos}
{}

Surface::~Surface() {
}

namespace{
	std::vector<Triangle> continuous_split(Triangle t, std::vector<Triangle> splits){
		std::vector<Triangle> tris{t};
		while(splits.size()){
			Vector<> normal = splits.back().normal();
			Vector<> pos = splits.back()[0];
			splits.pop_back();
			std::vector<Triangle> tmp_tris;
			for(Triangle tri : tris){
				auto new_tri = tri.split(pos, normal);
				tmp_tris.insert(tmp_tris.end(), new_tri.begin(), new_tri.end());
			}
			tris = tmp_tris;
		}
		return tris;
	}
	
	std::vector<Triangle> split_many(std::vector<Triangle> t, std::vector<Triangle> splits){
		std::vector<Triangle> result;
		for(Triangle tri : t){
			std::vector<Triangle> intersections;
			for(Triangle tris : splits){
				if(tri.intersectionWith(tris).first){
					intersections.push_back(tris);
				}
			}
			if(intersections.size()==0){
				result.push_back(tri);
				continue;
			}
			auto tmp = continuous_split(tri, intersections);
			result.insert(result.end(), tmp.begin(), tmp.end());
		}
		return result;
	}
}

Surface Surface::unite(Surface a, Surface b){
	for(auto& v : b.mesh.vertecies()){
		v.position += b.position - a.position;
	}
	Surface ret(a.position + Vector<>{5,0,0});
	auto a_test = [&](Triangle t){
	              		Vector<> avg = (t[0] + t[1] + t[2])/3.0;
	              		return !b.pointIsWithin(avg);
	                };
	auto b_test = [&](Triangle t){
	              		Vector<> avg = (t[0] + t[1] + t[2])/3.0;
	              		return !a.pointIsWithin(avg);
	              	};
	std::vector<Triangle> t_a = a.mesh.all_triangles();
	std::vector<Triangle> t_b = b.mesh.all_triangles();
	
	auto s_a = split_many(t_a, t_b);
	auto s_b = split_many(t_b, t_a);
	
	for(Triangle t : s_a){
		if(a_test(t)){
			//ret.mesh.add(t);
		}
	}
	for(Triangle t : s_b){
		if(b_test(t)){
			//ret.mesh.add(t);
		}
	}
	return ret;
}

Surface Surface::intersect(Surface a, Surface b){
	for(auto& v : b.mesh.vertecies()){
		v.position += b.position - a.position;
	}
	Surface ret(a.position + Vector<>{5,0,0});
	auto a_test = [&](Triangle t){
	              		Vector<> avg = (t[0] + t[1] + t[2])/3.0;
	              		return a.pointIsWithin(avg);
	                };
	auto b_test = [&](Triangle t){
	              		Vector<> avg = (t[0] + t[1] + t[2])/3.0;
	              		return b.pointIsWithin(avg);
	              	};
	std::vector<Triangle> t_a = a.mesh.all_triangles();
	std::vector<Triangle> t_b = b.mesh.all_triangles();
	
	auto s_a = split_many(t_a, t_b);
	auto s_b = split_many(t_b, t_a);
	
	for(Triangle t : s_a){
		if(a_test(t)){
			//ret.mesh.add(t);
		}
	}
	for(Triangle t : s_b){
		if(b_test(t)){
			//ret.mesh.add(t);
		}
	}
	return ret;
}

void Surface::Unite(Surface a){
	/* Deprecated */
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
	params.mul(2*PI);
	double arr[3] = {cos(params[0])*(1 + 0.25*cos(params[1])),
	                 sin(params[0])*(1 + 0.25*cos(params[1])),
	                 0.25*sin(params[1])};
	return Vector<>(arr);
}

namespace{
	void rotate_point(Vector<>& point, Vector<> axis, double angle){
		axis.make_unit();
		const Vector<> r1{cos(angle) + axis[0]*axis[0]*(1 - cos(angle)),
		          axis[0]*axis[1]*(1 - cos(angle)) - axis[2]*sin(angle),
		          axis[0]*axis[2]*(1 - cos(angle)) + axis[1]*sin(angle)};
		const Vector<> r2{axis[1]*axis[0]*(1 - cos(angle)) + axis[2]*sin(angle),
		          cos(angle) + axis[1]*axis[1]*(1 - cos(angle)),
		          axis[1]*axis[2]*(1 - cos(angle)) - axis[0]*sin(angle)};
		const Vector<> r3{axis[2]*axis[0]*(1 - cos(angle)) - axis[1]*sin(angle),
		                 axis[2]*axis[1]*(1 - cos(angle)) + axis[0]*sin(angle),
		                 cos(angle) + axis[2]*axis[2]*(1 - cos(angle))};
		const Vector<> tmp = point;
		point = {Vector<>::mul_comp(r1, tmp).sum_comp(),
		         Vector<>::mul_comp(r2, tmp).sum_comp(),
		         Vector<>::mul_comp(r3, tmp).sum_comp()};
	}
}

void Surface::rotate(Vector<> axis, double angle){
	bound_box[0] = bound_box[1] = position;
	for(auto& p: mesh.vertecies()){
		rotate_point(p.position, axis, angle);
		bound_box[0].set_min_comp(p.position);
		bound_box[1].set_max_comp(p.position);
	}
}
