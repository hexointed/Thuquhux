/* 
 * File:   Triangle.h
 * Author: Elias Forsberg
 *
 * Created on May 23, 2013, 7:11 PM
 */

#ifndef TRIANGLE_H
#define	TRIANGLE_H

#include "Geometry.h"
#include <vector>

namespace Geometry{
	
	class Triangle : public Polygon<3>{
	public:
		using Polygon<3>::Polygon;
		
		Triangle& move(const Geometry::Vector<> diff);
		Triangle operator +(const Geometry::Vector<> a);
		
		bool shares_side(const Triangle& with);
		bool passesThrough(Geometry::Vector<>& max, Geometry::Vector<>& min);
		std::pair<bool, Geometry::Vector<>> intersectionWith(Polygon<2> a) const;
		std::pair<bool, std::vector<Geometry::Vector<>>> intersectionWith(Triangle a) const;
		std::vector<Triangle> split(Geometry::Vector<> pos, Geometry::Vector<> normal) const;
		
		Geometry::Vector<> normal() const;
		void draw();
	};
}

#endif	/* TRIANGLE_H */
