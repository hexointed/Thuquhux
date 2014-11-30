/* 
 * File:   Paramertic_Surface.cpp
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

Surface::Surface(const Surface& orig):
	mesh{orig.mesh},
	mesh_detail{orig.mesh_detail},
	mesh_length{orig.mesh_length},
	prop_updated{orig.prop_updated},
	volume{orig.volume},
	bound_box{orig.bound_box[0], orig.bound_box[1]},
	position{orig.position}
{}

Surface::Surface(Vector<> pos):
	mesh_detail{10},
	mesh_length{mesh_detail*mesh_detail*2},
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
	for(Vector<>& v : b.mesh.vertecies()){
		v += b.position - a.position;
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
	for(Vector<>& v : b.mesh.vertecies()){
		v += b.position - a.position;
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
	for(PointVector<>& v : a.mesh.vertecies()){
		v += rel_pos;
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

bool Surface::pointIsWithin(Vector<> p){
	if(p.is_min_comp(bound_box[0]) || p.is_max_comp(bound_box[1]))
		return false;
	Vector<> min {p.getdx(), p.getdy(), bound_box[0].getdz()};
	Vector<> max {p.getdx(), p.getdy(), bound_box[1].getdz()};
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
	          [](Vector<> a, Vector<> b){return a.getdz()<b.getdz();});
	bool state = false;
	for(Vector<> pos: clips){
		state = !state;
		if(pos.getdz() > p.getdz())
			return !state;
	}
	return false;
}

Vector<> Geometry::def_param_axis_func(Vector<2> params){
	params.mul(2*PI);
	double arr[3] = {cos(params.getdx())*(1 + 0.25*cos(params.getdy())),
	                 sin(params.getdx())*(1 + 0.25*cos(params.getdy())),
	                 0.25*sin(params.getdy())};
	return Vector<>(arr);
}

namespace {
	void rotate_point(Vector<>& point, Vector<> axis, double angle){
		axis.make_unit();
		const Vector<> r1{cos(angle) + axis.getdx()*axis.getdx()*(1 - cos(angle)),
		          axis.getdx()*axis.getdy()*(1 - cos(angle)) - axis.getdz()*sin(angle),
		          axis.getdx()*axis.getdz()*(1 - cos(angle)) + axis.getdy()*sin(angle)};
		const Vector<> r2{axis.getdy()*axis.getdx()*(1 - cos(angle)) + axis.getdz()*sin(angle),
		          cos(angle) + axis.getdy()*axis.getdy()*(1 - cos(angle)),
		          axis.getdy()*axis.getdz()*(1 - cos(angle)) - axis.getdx()*sin(angle)};
		const Vector<> r3{axis.getdz()*axis.getdx()*(1 - cos(angle)) - axis.getdy()*sin(angle),
		                 axis.getdz()*axis.getdy()*(1 - cos(angle)) + axis.getdx()*sin(angle),
		                 cos(angle) + axis.getdz()*axis.getdz()*(1 - cos(angle))};
		const Vector<> tmp = point;
		point = {Vector<>::mul_dot(r1, tmp),
		         Vector<>::mul_dot(r2, tmp),
		         Vector<>::mul_dot(r3, tmp)};
	}
}

void Surface::rotate(Vector<> axis, double angle){
	bound_box[0] = bound_box[1] = position;
	for(Vector<>& p: mesh.vertecies()){
		rotate_point(p, axis, angle);
		bound_box[0].set_min_comp(p);
		bound_box[1].set_max_comp(p);
	}
}
