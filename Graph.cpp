/* 
 * File:   Graph.cpp
 * Author: elias
 * 
 * Created on May 19, 2013, 2:50 PM
 */

#include "Graph.h"
#include "PointVector.h"

Graph::Graph() {
}

Graph::Graph(const Graph& orig) {
}

Graph::~Graph() {
}

void Graph::addVertecies(PointVector<>** verts, int length){
	for(int i = 0; i < length; i++){
		vertecies[i] = verts[i];
	}
}

void Graph::connect(PointVector<>* a, PointVector<>* b, PointVector<>* c){
	PointVector<>* arr[3] = {a, b, c};
	triangles.push_back(new Triangle(arr));
}