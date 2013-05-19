/* 
 * File:   Graph.cpp
 * Author: elias
 * 
 * Created on May 19, 2013, 2:50 PM
 */

#include "Graph.h"

Graph::Graph() {
}

Graph::Graph(const Graph& orig) {
}

Graph::~Graph() {
}

void Graph::addVertex(PointVector<> p){
	vmap::iterator itr = vertecies.begin();
	itr = vertecies.find(p);
	if(itr==vertecies.end()){
		Vertex v(p);
		vertecies[p] = v;
		return;
	}
}

void Graph::connect(PointVector<>& a, PointVector<>& b, PointVector<>& c){
	addVertex(a);
	addVertex(b);
	addVertex(c);
	vmap::iterator itra = vertecies.find(a);
	vmap::iterator itrb = vertecies.find(b);
	vmap::iterator itrc = vertecies.find(c);
	itra->second.adjecent.push_back(std::make_pair(&(*itrb).second,&(*itrc).second));
}