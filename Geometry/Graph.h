/* 
 * File:   Graph.h
 * Author: elias
 *
 * Created on May 19, 2013, 2:50 PM
 */

#ifndef GRAPH_H
#define	GRAPH_H

#include <vector>
#include <map>
#include "../PointVector.h"
#include "Geometry.h"

using Geometry::Triangle;

namespace Geometry{
	class Graph {
	public:
		Graph(PointVector<>** verts, int length, int width);
		Graph(const Graph& orig);
		virtual ~Graph();
		
		int getVertexSize();
		void getResult(PointVector<>* verts);
	
	private:
		typedef std::vector<Triangle(*)> trivec;
		trivec triangles;
		PointVector<>* vertecies;
	
	};
}

#endif	/* GRAPH_H */