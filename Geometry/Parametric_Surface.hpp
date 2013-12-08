/* 
 * File:   Parametric_Surface.hpp
 * Author: Elias Forsberg
 *
 * Created on  June 1, 2013, 10:26 AM
 */

#ifndef PARAMETRIC_SURFACE_HPP
#define	PARAMETRIC_SURFACE_HPP

#include <iostream>
#include "Parametric_Surface.h"
#include "PointVector.h"
#include "Geometry.h"
#include "GL/freeglut.h"
#include <vector>

template<typename Functor>
Geometry::Parametric_Surface::Parametric_Surface(Functor f, PointVector<> pos):
	mesh_detail{10},
	mesh_length{mesh_detail*mesh_detail*2},
	bound_box{{0,0,0},{0,0,0}},
	position{pos}
{
	//mesh_vertecies.reserve(mesh_length);
	calculate_mesh(f);
}

	
/*This method calculates all vertecies using a parametric function pfunc*/
template<typename Functor>
void Geometry::Parametric_Surface::calculate_mesh(Functor pfunc){
	std::vector<PointVector<>> vertecies;
	vertecies.reserve(mesh_detail*mesh_detail);
	for(double t = 0; t < 1; t += 1.0/mesh_detail){
		for(double u = 0; u < 1; u += 1.0/mesh_detail){		
			//iterate through all points we need from pfunc
			PointVector<2> params(t,u);
			vertecies.push_back(pfunc(params));
			bound_box[0].set_min_comp(vertecies.back());
			bound_box[1].set_max_comp(vertecies.back());
		}
	}
	int ml = mesh_detail * mesh_detail;
	for(int i = 0; i < mesh_detail; ++i){
		for(int n = 0; n < mesh_detail; ++n){
			//"connect" the points, so that they can be drawn using Triangle methods
			mesh_vertecies.add(Triangle{vertecies[(i* mesh_detail + n) % ml], 
			                            vertecies[(i* mesh_detail + n  + 1) % ml],
			                            vertecies[((i+1)*mesh_detail + n) % ml]});
			mesh_vertecies.add(Triangle{vertecies[((i+1)*mesh_detail + n) % ml], 
			                            vertecies[(i* mesh_detail + n  + 1) % ml],
			                            vertecies[((i+1)*mesh_detail + n + 1) % ml]});
		}
	}
}

#endif	/* PARAMETRIC_SURFACE_HPP */
