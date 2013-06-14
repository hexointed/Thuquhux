/* 
 * File:   Parametric_Surface.hpp
 * Author: Elias Forsberg
 *
 * Created on June 1, 2013, 10:26 AM
 */

#ifndef PARAMETRIC_SURFACE_HPP
#define	PARAMETRIC_SURFACE_HPP

#include "Parametric_Surface.h"
#include "PointVector.h"
#include <vector>

template<typename Functor>
Geometry::Parametric_Surface::Parametric_Surface(Functor f):
	mesh_detail(400),
	mesh_length((mesh_detail + 2)*(mesh_detail + 1)*2)
{
	mesh_vertecies.push_back(new PointVector<>[mesh_length]);

	this->bound_box[0] = new PointVector<>(0,0,0);
	this->bound_box[1] = new PointVector<>(0,0,0);
	
	this->position = new PointVector<>(0,0,0);
	calculate_mesh(f);
}

template<typename Functor>
void Geometry::Parametric_Surface::calculate_mesh(Functor pfunc){
	int count = 0;
	for(double t = 0; t <= 1 + 1.0/mesh_detail; t += 1.0/mesh_detail){
		for(double u = 0; u <= 1; u += 1.0/mesh_detail){
			PointVector<2> params(t,u);
			PointVector<2> dparams(t + 1.0/mesh_detail,u);
			PointVector<> p(pfunc(params));
			PointVector<> dp(pfunc(dparams));
			mesh_vertecies.at(0)[count] = p;
			mesh_vertecies.at(0)[count +1] = dp;
			bound_box[0]->set_min_comp(p);
			bound_box[1]->set_max_comp(p);
			count += 2;
		}
	}
}

#endif	/* PARAMETRIC_SURFACE_HPP */