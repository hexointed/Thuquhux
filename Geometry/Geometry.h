/* 
 * File:   Triangle.h
 * Author: Elias Forsberg
 * 
 * Created on May 23, 2013, 7:11 PM
 * 
 * 
 */

#ifndef GEOMETRY_H
#define	GEOMETRY_H

#include "PointVector.h"
#include <vector>

namespace Geometry{
	
	template<const int Sides, const int Dim = 3>
	class Polygon{
	public:
		friend class Triangle;
		
		Polygon() = default;
		template<typename Head, typename... Trail>
		Polygon(Head head, Trail... trail);
		Polygon(PointVector<Dim>* sides);
		virtual ~Polygon() = default;
		
		PointVector<Dim> vertecies[Sides];
	};
	
	class Triangle {
	public:
		explicit Triangle() = default;
		Triangle(const Triangle& orig) = default;
		Triangle(PointVector<>* sides);
		explicit Triangle(PointVector<> a, PointVector<> b, PointVector<> c);
		~Triangle();
		
		Triangle& move(const PointVector<> diff);
		Triangle operator +(const PointVector<> a);
		Triangle& operator =(const Triangle& a) = default;
		PointVector<>& operator[](const int vertex);
		
		bool shares_side(const Triangle& with);
		bool passesThrough(PointVector<>& max, PointVector<>& min);
		std::pair<bool, PointVector<>> intersectionWith(Polygon<2> a) const;
		std::pair<bool, std::vector<PointVector<>>> intersectionWith(Triangle a) const;
		std::vector<Triangle> split(PointVector<> pos, PointVector<> normal) const;
		
		PointVector<> normal() const;
		void draw();
	
	private:	
		PointVector<> vertecies[3];
	};
}

#endif	/* GEOMETRY_H */
