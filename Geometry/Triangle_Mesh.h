/* 
 * File:   Triangle_Mesh.h
 * Author: elias
 *
 * Created on September 6, 2013, 5:36 PM
 */

#ifndef TRIANGLE_MESH_H
#define	TRIANGLE_MESH_H

#include <vector>
#include <map>
#include <set>

#include "Geometry.h"

namespace Geometry{

	class Triangle_Mesh {	
		/* Helper classes Element and Iterator:
		 * Element is used to keep track of a single Triangle, along with the Triangles it
		 * is connected to.
		 * Iterator is used so that Triangle_Meshes easily can be used with different
		 * kinds of loops.
		 */
	public:
		class Iterator;
	private:	
		class Element{
		public:
			Element();
			Element& first_valid_connection();
			bool single_valid_connection();
			bool connected_with(const Element& e);
			
		public:
			Triangle* tri;
			Element* connected[3];
			
		public:
			struct Elementcompare{
				bool operator()(Element a, Element b){
					return a.tri < b.tri;
				}
			};
		};
		
		using Element_set = std::set<Element, Element::Elementcompare>;
		using Element_map = std::map<Element, Element, Element::Elementcompare>;
		
		/* Declarations for class Triangle_Mesh :
		 */
	public:
		Triangle_Mesh() = default;
		
	public:
		template<template <typename> class Container>
		static Container<Triangle_Mesh> make_mesh(Container<Triangle*> triangles);
		
		template<template <typename> class Container>
		static Triangle_Mesh make_mesh(Container<PointVector<> > mesh_vertecies);
		
		std::vector<Triangle_Mesh> intersection(Triangle_Mesh a);
		Triangle& operator[](const int i);
		long int size();
		
		Triangle_Mesh get_single_path(Element& begin, Element& end);
		bool is_loop();
		
		static void test();
		
		void add(Triangle t);
		void add(Triangle& t);
		void remove(const Triangle& t);
		
	private:
		std::vector<Element> elem;
		
	private:
		Triangle_Mesh construct_mesh(Element a, Element b, Element_map c);
		
	public:
		Iterator begin() {return Iterator{elem.begin()};}
		Iterator end() {return Iterator{elem.end()};}
		using iterator = Iterator;
		
		class Iterator{
		public:
			Iterator(decltype(elem)::iterator i){
				it = i;
			}
			
			Triangle&	operator *();
			Iterator	operator++();
			Iterator	operator++(int);
			Iterator	operator--();
			Iterator	operator--(int);
			Iterator	operator +(int p) const;
			Iterator	operator -(int p) const;
			int			operator -(Iterator i) const;
			bool		operator!=(Iterator i) const;
			
		private:
			decltype(elem)::iterator it;
		};

	};
}

#endif	/* TRIANGLE_MESH_H */

#include "Triangle_Mesh.hpp"
