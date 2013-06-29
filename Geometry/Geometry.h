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
		Polygon();
		Polygon(PointVector<Dim>* sides);
		//Polygon(const Polygon<Sides, Dim>& orig);
		virtual ~Polygon();
		
		PointVector<Dim> vertecies[Sides];
	};
	
	class Triangle : public Polygon<3> {
	public:
		Triangle(PointVector<>* sides);
		//Triangle(const Triangle& orig);
		virtual ~Triangle();
		
		bool passesThrough(PointVector<>& max, PointVector<>& min);
		std::pair<bool, std::vector<PointVector<>>> collisionWith(Triangle a);
		void draw();
	};
}

#endif	/* GEOMETRY_H */