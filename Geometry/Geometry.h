/* 
 * File:   Triangle.h
 * Author: elias
 *
 * Created on May 23, 2013, 7:11 PM
 */

#ifndef GEOMETRY_H
#define	GEOMETRY_H

#include "PointVector.h"
#include <vector>

namespace Geometry{
	
	template<const int Sides, const int Dim = 3>
	class Polygon{
	public:
		Polygon() = default;
		template<typename Head, typename... Trail>
		Polygon(Head head, Trail... trail);
		Polygon(PointVector<Dim>* sides);
		virtual ~Polygon() = default;
		
		PointVector<Dim> vertecies[Sides];
	};
	
	class Triangle : public Polygon<3> {
	public:
		Triangle(PointVector<>* sides);
		virtual ~Triangle() = default;
		
		bool passesThrough(PointVector<>& max, PointVector<>& min);
		std::pair<bool, PointVector<>> intersectionWith(Polygon<2> a);
		std::pair<bool, std::vector<PointVector<>>> intersectionWith(Triangle a);
		void draw();
	};
}

#endif	/* GEOMETRY_H */