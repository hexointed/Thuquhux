/*
 * File: Polytope.h
 * Author: Elias Forsberg
 *
 * Created on: December 21, 2013, 09:16 AM
 */
 
#ifndef POLYTOPE_CPP
#define POLYTOPE_CPP

#include "PointVector.h"

template<typename CRTP, int N_vertecies, typename Vertex_type>
class Polytope_impl{
protected:
	using Vertex_list = std::initializer_list<Vertex_type>;
public:
	Polytope_impl() = default;
	Polytope_impl(const Polytope_impl&) = default;
	Polytope_impl(Polytope_impl&&) = default;
	
	explicit Polytope_impl(Vertex_list vertecies);
	explicit Polytope_impl(Vertex_type* vertecies);

private:
	Vertex_type vertecies[N_vertecies];
	
public:
	Polytope_impl& operator =(const Polytope_impl&) = default;
	Polytope_impl& operator =(Polytope_impl&&) = default;
	
	Vertex_type& operator[](int vertex) const;
	Vertex_type center() const;
	
	CRTP& move_center(Vertex_type pos);
	CRTP& move_relative(Vertex_type diff);
};

template<int N_vertecies, typename Vertex_type = PointVector<3, double>>
class Polytope : 
	public Polytope_impl<Polytope<N_vertecies, Vertex_type>, N_vertecies, Vertex_type>{
public:
	using Polytope::Polytope_impl::Polytope_impl;
};

#include "Polytope.hpp"

#endif /* POLYTOPE_CPP */
