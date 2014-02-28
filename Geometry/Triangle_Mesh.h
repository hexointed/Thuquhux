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
	
	/*
	 * Triangle_Mesh provides ways to iterate through both it's Triangles
	 * (with begin() and end()) and vertecies (with vertecies().begin() 
	 * etc.)
	 */
	
	class Triangle_Mesh{
	public:
		class Element;
		class Iterator;
		
	public:
		Triangle_Mesh() = default;
		Triangle_Mesh(const Triangle_Mesh& orig) = default;
		Triangle_Mesh(Triangle_Mesh&& orig) = default;
		
		Triangle_Mesh(std::vector<Geometry::Vector<>> p);
		Triangle_Mesh(std::vector<Geometry::Vector<>> p, std::vector<int> i);
		
		Triangle_Mesh& operator=(const Triangle_Mesh& orig) = default;
		Triangle_Mesh& operator=(Triangle_Mesh&& orig) = default;
		
	private:
		std::vector<Geometry::Vector<>> vertex;
		std::vector<int> index;
		
	public:
		size_t size() const;
		
		void add(std::vector<Geometry::Vector<>> p);
		void add(const Triangle_Mesh& t);
		
		std::vector<Geometry::Vector<>>& vertecies() {return vertex;}
		std::vector<int>& indices() {return index;}
		
		std::vector<Triangle> all_triangles();
		std::vector<Triangle> intersecting_triangles(Triangle t);
		
		Iterator begin();
		Iterator end();
	};
	
	/*
	 * Triangle_Mesh::Element provides access to the vertecies of a Triangle_Mesh, 
	 * grouping them together as Triangles. The same vertex may occur in several Elements.
	 */
	
	class Triangle_Mesh::Element{
	public:
		Element(Triangle_Mesh& t, int a, int b, int c);
	private:
		int vertecies[3];
		Triangle_Mesh& super;
	public:
		operator Geometry::Triangle () const;
		Geometry::Vector<>& operator[](int i);
	};
	
	/*
	 * Triangle_Mesh::Iterator is a simple random access relative iterator. An Iterator
	 * remains valid as long as vertecies are not deleted from its Triangle_Mesh.
	 */
	
	class Triangle_Mesh::Iterator{
	public:
		Iterator(Triangle_Mesh& s, int p);
		Iterator(const Iterator&) = default;
		Iterator(Iterator&&) = default;
		
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
