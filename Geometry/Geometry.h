/* 
 * File:   Triangle.h
 * Author: elias
 *
 * Created on May 23, 2013, 7:11 PM
 */

#ifndef GEOMETRY_H
#define	GEOMETRY_H

#include "../PointVector.h"

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
		bool collisionWith(Triangle& a);
		void draw();
		
	private:
		bool coll(Triangle& a);
	};
}

#endif	/* GEOMETRY_H */