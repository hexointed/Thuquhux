/*
 * File: Polytope.h
 * Author: Elias Forsberg
 *
 * Created on: December 21, 2013, 09:16 AM
 */
 
#ifndef POLYTOPE_CPP
#define POLYTOPE_CPP

#include "PointVector.h"

template<int N_vertecies, typename Vertex_type = PointVector<3, double>>
class Polytope{
protected:
	using Vertex_list = std::initializer_list<Vertex_type>;
public:
	Polytope() = default;
	Polytope(const Polytope&) = default;
	Polytope(Polytope&&) = default;
	
	Polytope(Vertex_list vertecies);
	Polytope(Vertex_type* vertecies);

private:
	Vertex_type vertecies[N_vertecies];
	
public:
	Polytope& operator =(const Polytope&) = default;
	Polytope& operator =(Polytope&&) = default;
	
	Vertex_type& operator[](int vertex) const;
	
	Polytope& move_center(Vertex_type pos);
	Polytope& move_relative(Vertex_type diff);
};

#endif /* POLYTOPE_CPP */
