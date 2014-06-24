/* 
 * File:   Surface.hpp
 * Author: Elias Forsberg
 *
 * Created on  June 1, 2013, 10:26 AM
 */

#ifndef PARAMETRIC_SURFACE_HPP
#define	PARAMETRIC_SURFACE_HPP

#include <iostream>
#include "Surface.h"
#include "Geometry.h"
#include "GL/freeglut.h"
#include <vector>

template<typename Functor>
Geometry::Surface::Surface(Functor f, Geometry::Vector<> pos):
	mesh_detail{8},
	mesh_length{mesh_detail*mesh_detail*2},
	bound_box{{0,0,0},{0,0,0}},
	position{pos}
{
	calculate_mesh(f);
}

	
/*This method calculates all vertecies using a parametric function pfunc*/
template<typename Functor>
void Geometry::Surface::calculate_mesh(Functor pfunc){
	std::vector<Geometry::Vector<>> vertecies;
	vertecies.reserve(mesh_detail*mesh_detail);
	for(double t = 0; t < 1; t += 1.0/mesh_detail){
		for(double u = 0; u < 1; u += 1.0/mesh_detail){		
			//iterate through all points we need from pfunc
			Geometry::Vector<2> params({t,u});
			vertecies.push_back(pfunc(params));
			bound_box[0].set_min_comp(vertecies.back());
			bound_box[1].set_max_comp(vertecies.back());
		}
	}
	int ml = mesh_detail * mesh_detail;
	std::vector<int> indices;
	for(int i = 0; i < mesh_detail; ++i){
		for(int n = 0; n < mesh_detail + 1; ++n){
			//"connect" the points, so that they can be drawn using Triangle methods
			indices.push_back( ( i    * mesh_detail + n) % ml);
			indices.push_back( ((i+1) * mesh_detail + n) % ml);
			/*
			mesh.add(Triangle{vertecies[(i* mesh_detail + n) % ml], 
			                  vertecies[(i* mesh_detail + n  + 1) % ml],
			                  vertecies[((i+1)*mesh_detail + n) % ml]});
			                  
			mesh.add(Triangle{vertecies[((i+1)*mesh_detail + n) % ml], 
			                  vertecies[(i* mesh_detail + n  + 1) % ml],
			                  vertecies[((i+1)*mesh_detail + n + 1) % ml]});*/
		}
		indices.push_back( ((i+1) * mesh_detail + mesh_detail) % ml);
		indices.push_back( ((i+1) * mesh_detail + 0 ) % ml);
	}
	mesh.add(Triangle_Mesh{vertecies, indices});
}

#endif	/* PARAMETRIC_SURFACE_HPP */
