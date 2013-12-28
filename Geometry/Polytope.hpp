/*
 * File: Polytope.hpp
 * Author: Elias Forsberg
 *
 * Created on: December 24, 2013, 10:26 AM
 */
 
#ifndef POLYTOPE_HPP
#define POLYTOPE_HPP

#include "Polytope.h"

template<typename CRTP, int N_vertecies, typename Vertex_type>
Polytope_impl<CRTP, N_vertecies, Vertex_type>::Polytope_impl(Vertex_list verts) {
	int i = 0;
	for(Vertex_type v : verts){
		vertecies[i] = v;
		i++;
	}
}

template<typename CRTP, int N_vertecies, typename Vertex_type>
Polytope_impl<CRTP, N_vertecies, Vertex_type>::Polytope_impl(Vertex_type* verts) {
	for(int i = 0; i < N_vertecies; i++){
		vertecies[i] = verts[i];
	}
}

template<typename CRTP, int N_vertecies, typename Vertex_type>
Vertex_type& Polytope_impl<CRTP, N_vertecies, Vertex_type>::operator[](int vertex) const {
	return vertecies[vertex];
}

template<typename CRTP, int N_vertecies, typename Vertex_type>
Vertex_type Polytope_impl<CRTP, N_vertecies, Vertex_type>::center() const {
	Vertex_type avg_pos;
	for(Vertex_type v : vertecies){
		avg_pos += v;
	}
	return avg_pos / (double)N_vertecies;
}

template<typename CRTP, int N_vertecies, typename Vertex_type>
CRTP& Polytope_impl<CRTP, N_vertecies, Vertex_type>::move_center(Vertex_type pos) {
	return move_relative(pos - center());
}

template<typename CRTP, int N_vertecies, typename Vertex_type>
CRTP& Polytope_impl<CRTP, N_vertecies, Vertex_type>::move_relative(Vertex_type diff) {
	for(Vertex_type& v : vertecies){
		v += diff;
	}
	return *this;
}

#endif /* POLYTOPE_HPP */
