/* 
 * File:   Paramertic_Surface.cpp
 * Author: Elias Forsberg
 * 
 * Created on April 24, 2013, 4:42 PM
 */
#include "PointVector.h"
#include "Parametric_Surface.h"
#include "Geometry.h"
#include <math.h>

#include "GL/freeglut.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using Geometry::Parametric_Surface;
using Geometry::Triangle;

double PI = 3.14159265358979;

Parametric_Surface::Parametric_Surface(const Parametric_Surface& orig):
	mesh{orig.mesh},
	mesh_detail{orig.mesh_detail},
	mesh_length{orig.mesh_length},
	prop_updated{orig.prop_updated},
	volume{orig.volume},
	bound_box{orig.bound_box[0], orig.bound_box[1]},
	position{orig.position}
{}

Parametric_Surface::Parametric_Surface(PointVector<> pos):
	mesh_detail{10},
	mesh_length{mesh_detail*mesh_detail*2},
	bound_box{{0,0,0},{0,0,0}},
	position{pos}
{}

Parametric_Surface::~Parametric_Surface() {
}

namespace{
	std::vector<Triangle> continuous_split(Triangle t, std::vector<Triangle> splits){
		std::vector<Triangle> tris{t};
		while(splits.size()){
			PointVector<> normal = splits.back().normal();
			PointVector<> pos = splits.back()[0];
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

Parametric_Surface Parametric_Surface::Union(Parametric_Surface a, Parametric_Surface b){
	Parametric_Surface ret(a.position + PointVector<>{5,0,0});
	auto a_test = [&](Triangle t){
	              		PointVector<> avg = (t[0] + t[1] + t[2])/3.0;
	              		return !b.pointIsWithin(avg);
	                };
	auto b_test = [&](Triangle t){
	              		PointVector<> avg = (t[0] + t[1] + t[2])/3.0;
	              		return !a.pointIsWithin(avg);
	              	};
	std::vector<Triangle> t_a = a.mesh.all_triangles();
	std::vector<Triangle> t_b = b.mesh.all_triangles();
	
	auto s_a = split_many(t_a, t_b);
	auto s_b = split_many(t_b, t_a);
	
	for(Triangle t : s_a){
		if(a_test(t)){
			ret.mesh.add(t);
		}
	}
	for(Triangle t : s_b){
		if(b_test(t)){
			ret.mesh.add(t);
		}
	}
	return ret;
}

void Parametric_Surface::Unite(Parametric_Surface a){
	/* Deprecated */
	PointVector<> rel_pos = a.position - position;
	bound_box[0].set_min_comp(a.bound_box[0] + rel_pos);
	bound_box[1].set_max_comp(a.bound_box[1] + rel_pos);
	for(Triangle tri: a.mesh){
		mesh.add(Triangle{tri + rel_pos});
	}
	
	std::cout<<mesh.size()<<std::endl;
}

bool Parametric_Surface::is_subset_of(const Parametric_Surface& v){
	PointVector<> p = bound_box[1];
	PointVector<> q = v.bound_box[1];
	PointVector<> r = bound_box[0];
	PointVector<> s = v.bound_box[0];
	
	return	p.add(position).is_min_comp(q.add(v.position)) && 
	        r.add(position).is_max_comp(s.add(v.position));
}

bool Parametric_Surface::is_superset_of(const Parametric_Surface& v){
	auto p = bound_box[1];
	auto q = v.bound_box[1];
	auto r = bound_box[0];
	auto s = v.bound_box[0];
	return p.add(position).is_max_comp(q.add(v.position)) &&
	       r.add(position).is_min_comp(s.add(v.position));
}

bool Parametric_Surface::isIntersecting(const Parametric_Surface& v){
	auto p = bound_box[1];
	auto q = v.bound_box[1];
	auto r = bound_box[0];
	auto s = v.bound_box[0];
	return p.add(position).is_max_comp(s.add(v.position)) &&
	       r.add(position).is_min_comp(q.add(v.position));
}

bool Parametric_Surface::pointIsWithin(PointVector<> p){
	if(p.is_min_comp(bound_box[0]) || p.is_max_comp(bound_box[1]))
		return false;
	PointVector<> min {p.getdx(), p.getdy(), bound_box[0].getdz()};
	PointVector<> max {p.getdx(), p.getdy(), bound_box[1].getdz()};
	Polygon<2> clip_line;
	clip_line.vertecies[0] = min;
	clip_line.vertecies[1] = max;
	std::vector<PointVector<>> clips;
	for(Triangle tri: mesh){
		auto tmp = tri.intersectionWith(clip_line);
		if(tmp.first)
			clips.push_back(tmp.second);
	}
	std::sort(clips.begin(), clips.end(), 
	          [](PointVector<> a, PointVector<> b){return a.getdz()<b.getdz();});
	bool state = false;
	for(PointVector<> pos: clips){
		state = !state;
		if(pos.getdz() > p.getdz())
			return !state;
	}
	return false;
}

PointVector<> Geometry::def_param_axis_func(PointVector<2> params){
	params.mul(2*PI);
	double arr[3] = {cos(params.getdx())*(1 + 0.25*cos(params.getdy())),
	                 sin(params.getdx())*(1 + 0.25*cos(params.getdy())),
	                 0.25*sin(params.getdy())};
	return PointVector<>(arr);
}

namespace{
	void rotate_point(PointVector<>& point, PointVector<> axis, double angle){
		axis.make_unit();
		static const PointVector<> r1{cos(angle) + axis.getdx()*axis.getdx()*(1 - cos(angle)),
		                 axis.getdx()*axis.getdy()*(1 - cos(angle)) - axis.getdz()*sin(angle),
		                 axis.getdx()*axis.getdz()*(1 - cos(angle)) + axis.getdy()*sin(angle)};
		static const PointVector<> r2{axis.getdy()*axis.getdx()*(1 - cos(angle)) + axis.getdz()*sin(angle),
		                 cos(angle) + axis.getdy()*axis.getdy()*(1 - cos(angle)),
		                 axis.getdy()*axis.getdz()*(1 - cos(angle)) - axis.getdx()*sin(angle)};
		static const PointVector<> r3{axis.getdz()*axis.getdx()*(1 - cos(angle)) - axis.getdy()*sin(angle),
		                 axis.getdz()*axis.getdy()*(1 - cos(angle)) + axis.getdx()*sin(angle),
		                 cos(angle) + axis.getdz()*axis.getdz()*(1 - cos(angle))};
		const PointVector<> tmp = point;
		point = {PointVector<>::mul_comp(r1, tmp).sum_comp(),
		         PointVector<>::mul_comp(r2, tmp).sum_comp(),
		         PointVector<>::mul_comp(r3, tmp).sum_comp()};
	}
}

void Parametric_Surface::rotate(PointVector<> axis, double angle){
	for(PointVector<>& p: mesh.vertecies()){
		rotate_point(p, axis, angle);
	}
	for(auto& point: bound_box){
		rotate_point(point, axis, angle);
	}
}

void Parametric_Surface::drawMesh(){
	glPushMatrix();
	glTranslatef(position.getdx(), position.getdy(), position.getdz());
	for(Triangle tri: mesh){
		tri.draw();
	}
	glPopMatrix();
}
