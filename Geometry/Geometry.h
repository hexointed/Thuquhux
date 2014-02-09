/*
 * File: Geometry.h
 * Author: Elias Forsberg
 *
 * Created on: February 9, 2014, 15:26
 */
 
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "PointVector.h"

namespace Geometry{
	template<int Dimension, typename Numeric = double>
	using Vector = PointVector<Dimension, Numeric>;
	
	template<typename Numeric = double>
	using Point = PointVector<3, Numeric>;
}

#include "Polytope.h"

namespace Geometry{
	using Line = Polytope<2, Vector<3>>;
	
	template<int Dimension>
	using Polygon = Polytope<Dimension, Vector<3>>;
}

#include "Triangle.h"

#endif /* GEOMETRY_H */
