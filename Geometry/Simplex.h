/*
 * File: Simplex.h
 * Author: Elias Forsberg
 *
 * Created on: December 21, 2013, 10:37 AM
 */
 
#ifndef SIMPLEX_H
#define SIMPLEX_H

#include "Polytope.h"

template<int N_simplex, typename Vertex_type = PointVector<3, double>>
class Simplex : public virtual Polytope<N_simplex, Vertex_type> {
	using Numeric = typename Vertex_type::Numeric_type;
public:
	Simplex() : Simplex::Polytope() {}
	Simplex(const Simplex& s) : Simplex::Polytope(s) {}
	Simplex(Simplex && s) : Simplex::Polytope(s) {}
	
	Simplex(std::initializer_list<Vertex_type> v) : Simplex::Polytope(v) {}
	Simplex(Vertex_type* p) : Simplex::Polytope(p) {}
	
public:
	Numeric volume() const;
	
};

#endif /* SIMPLEX_H */
