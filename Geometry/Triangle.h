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
		
		Triangle& move(const PointVector<> diff);
		Triangle operator +(const PointVector<> a);
		
		bool shares_side(const Triangle& with);
		bool passesThrough(PointVector<>& max, PointVector<>& min);
		std::pair<bool, PointVector<>> intersectionWith(Polygon<2> a) const;
		std::pair<bool, std::vector<PointVector<>>> intersectionWith(Triangle a) const;
		std::vector<Triangle> split(PointVector<> pos, PointVector<> normal) const;
		
		PointVector<> normal() const;
		void draw();
	};
}

#endif	/* TRIANGLE_H */
