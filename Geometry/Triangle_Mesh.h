/* 
 * File:   Triangle_Mesh.h
 * Author: Elias Forsberg
 *
 * Created on September 6, 2013, 5:36 PM
 */

#ifndef TRIANGLE_MESH_H
#define	TRIANGLE_MESH_H

#include <vector>

#include "PointVector.h"
#include "Geometry.h"

namespace Geometry{
	class Triangle_Mesh;
	
	class Element{
	public:
		Element(Geometry::Triangle t, Triangle_Mesh& universe);
	private:
		size_t vertecies[3];
		size_t connected[3];
		Triangle_Mesh& super;
	public:
		operator Geometry::Triangle ();
	};
	
	class Triangle_Mesh{
		friend class Element;
	public:
		Triangle_Mesh() = default;
		Triangle_Mesh(const Triangle_Mesh&) = default;
		Triangle_Mesh(std::vector<Geometry::Triangle> t);
		
	private:
		std::vector<PointVector<>> _vertecies;
		std::vector<Element> elements;
		
	public:
		size_t size();
		void add(Geometry::Triangle t);
		std::vector<PointVector<>>& vertecies() {return _vertecies;}
		
		std::vector<Triangle> all_triangles();
		std::vector<Triangle> intersecting_triangles(Triangle t);
		
		decltype(elements)::iterator begin(){return elements.begin();}
		decltype(elements)::iterator end(){return elements.end();}
	};
}

#endif	/* TRIANGLE_MESH_H */
