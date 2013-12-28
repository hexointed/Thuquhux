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
class Simplex : public virtual Polytope<N_simplex+1, Vertex_type> {
private:
	using Numeric = typename Vertex_type::Numeric_type;

public:
	using Simplex::Polytope::Polytope;
	
public:
	Numeric volume() const;
};

#endif /* SIMPLEX_H */


