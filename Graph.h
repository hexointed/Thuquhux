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
#include "PointVector.h"
#include "PointVector.cpp"

struct Vertex{
	typedef std::pair<Vertex*, Vertex*> ve;
	std::vector<ve> adjecent;
	PointVector<> position;
	Vertex(){}
	Vertex(PointVector<>& p){
		position = p;
	}
};

class Graph {
public:
	Graph();
	Graph(const Graph& orig);
	virtual ~Graph();
	
	void addVertex(PointVector<> p);
	void connect(PointVector<>& a, PointVector<>& b, PointVector<>& c);
	
private:
	typedef std::map<PointVector<>, Vertex> vmap;
	vmap vertecies;

};

#endif	/* GRAPH_H */

