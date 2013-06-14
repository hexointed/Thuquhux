/* 
 * File:   Graph.cpp
 * Author: elias
 * 
 * Created on May 19, 2013, 2:50 PM
 */

#include "Graph.h"
#include "PointVector.h"
#include "Geometry.h"

using Geometry::Graph;
using Geometry::Triangle;

Graph::Graph(PointVector<>** verts, int length, int width){
	for(int i = 0; i < length - 1; i++){
		for(int j = 0; j < width; j++){
			int pos = i*width + j;
			
		}
	}
}

Graph::Graph(const Graph& orig) {
}

Graph::~Graph() {
}

int Graph::getVertexSize(){
	return 0;
}