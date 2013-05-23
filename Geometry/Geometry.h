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
	class Polygon{
		
	};
	
	struct Triangle : public Polygon {
		Triangle();
		Triangle(const Triangle& orig);
		virtual ~Triangle();
		
		bool passesThrough(PointVector<>& a, PointVector<>& b);
		std::pair<PointVector<>, PointVector<> > collisionWith(Triangle& a);
	};
}

#endif	/* GEOMETRY_H */