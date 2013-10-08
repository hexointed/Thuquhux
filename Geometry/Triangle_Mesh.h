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

#include "Geometry.h"

namespace Geometry{

	class Triangle_Mesh {
	private:
		Triangle_Mesh() = default;
		class Element;
		
	public:
		template<template <typename> class Container>
		static Container<Triangle_Mesh> make_mesh(Container<Triangle*> triangles);
		
		template<template <typename> class Container>
		static Triangle_Mesh make_mesh(Container<PointVector<> > mesh_vertecies);
		
		Triangle& operator[](const int i);
		long int size();
		
		Triangle_Mesh get_single_path(Element& begin, Element& end);
		bool is_loop();
		
		void add(Triangle t);
		void remove(const Triangle& t);
		
	private:
		std::vector<Element> elem;
		
		class Element{
		public:
			Element() = default;
			Element& first_valid_connection();
			bool single_valid_connection();
			
		public:
			Triangle* tri;
			Element* connected[3];
			short connections;
			
		public:
			struct Elementcompare{
				bool operator()(Element a, Element b){
					return a.tri < b.tri;
				}
			};
		};	
	
	private:
		Triangle_Mesh construct_mesh(Element a, std::map<Element, Element, Element::Elementcompare> b);
		
	public:
		auto begin() -> decltype(elem.begin()){return elem.begin();}
		auto end() -> decltype(elem.end()){return elem.end();}
		using iterator = decltype(elem)::iterator;

	};
}

#endif	/* TRIANGLE_MESH_H */

#include "Triangle_Mesh.hpp"