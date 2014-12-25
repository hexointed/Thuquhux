/*
 * File:   Vertex.h
 * Author: Elias Forsberg
 *
 * Created on December 25, 2014, 15:58
 *
 * Vertex is used by Triangle_Mesh to store information about each vertex.
 */

#ifndef VERTEX_H
#define VERTEX_H

#include "Geometry.h"

namespace Geometry {
	
	class Vertex {
	public:
		Vertex() = default;
		Vertex(Geometry::Vector<> p) : position{p} {}
		
	public:
		Geometry::Vector<> position;
		
	public:
		operator Geometry::Vector<> (){
			return position;
		}
	};
	
}

#endif /* VERTEX_H */
