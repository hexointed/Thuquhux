/* 
 * File:   Triangle_Mesh.h
 * Author: Elias Forsberg
 *
 * Created on September 6, 2013, 5:36 PM
 *
 * The class Triangle_Mesh can be used to represent trees and graphs with
 * Triangle nodes. Mesh information is stored vertex-wise, to simplify
 * deformation of the mesh.
 */

#ifndef TRIANGLE_MESH_H
#define	TRIANGLE_MESH_H

#include <vector>

#include "Geometry.h"

namespace Geometry{
	class Triangle_Mesh;
	
	/*
	 * Element represents nodes in a graph. It can implicitly convert
	 * to a Triangle. Connecting nodes are stored in terms of their 
	 * positions in the parent Triangle_Mesh's _vertecies vector.
	 */
	
	class Element{
	public:
		Element(Geometry::Triangle t, Triangle_Mesh& universe);
	private:
		size_t vertecies[3];
		size_t connected[3];
		Triangle_Mesh& super;
	public:
		operator Geometry::Triangle () const;
	};
	
	/*
	 * Triangle_Mesh provides ways to iterate through both it's Triangles
	 * (with begin() and end()) and vertecies (with vertecies().begin() 
	 * etc.)
	 */
	
	class Triangle_Mesh{
		friend class Element;
		class Iterator;
	public:
		Triangle_Mesh() = default;
		Triangle_Mesh(const Triangle_Mesh& orig);
		Triangle_Mesh(std::vector<Geometry::Triangle> t);
		Triangle_Mesh& operator=(const Triangle_Mesh& orig);
		
	private:
		std::vector<PointVector<>> _vertecies;
		std::vector<Element> elements;
		
	public:
		size_t size();
		void add(Geometry::Triangle t);
		std::vector<PointVector<>>& vertecies() {return _vertecies;}
		
		std::vector<Triangle> all_triangles() const;
		std::vector<Triangle> intersecting_triangles(Triangle t);
		
		decltype(elements)::iterator begin(){return elements.begin();}
		decltype(elements)::iterator end(){return elements.end();}
		decltype(elements)::const_iterator begin() const {return elements.begin();}
		decltype(elements)::const_iterator end() const {return elements.end();}
	};
	
	class Triangle_Mesh::Iterator{
	public:
		Iterator(Triangle_Mesh& s, int p);
		Iterator(const Iterator&) = default;
		Iterator(const Iterator&&) = default;
		
	private:
		Triangle_Mesh& super;
		int pos;
	
	public:
		bool operator==(Iterator) const;
		bool operator!=(Iterator) const;
		bool operator <(Iterator) const;
		bool operator >(Iterator) const;
		bool operator<=(Iterator) const;
		bool operator>=(Iterator) const;
		
		Element operator *();
		const Element operator *() const;
		
		void operator++();
		void operator++(int);
		void operator--();
		void operator--(int);
		
		Iterator operator +(int) const;
		Iterator operator -(int) const;
		int operator -(Iterator) const;
		
		Element operator[](int);
		const Element operator[](int) const;
	};
}

#endif	/* TRIANGLE_MESH_H */
