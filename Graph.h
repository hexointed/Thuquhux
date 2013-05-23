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

struct Triangle{
	Triangle* adjacents[3];
	PointVector<>* vertecies[3];
	Triangle(){}
	Triangle(PointVector<>** verts){
		for(int i = 0; i < 3; i++){
			vertecies[i] = verts[i];
		}
	}
};

class Graph {
public:
	Graph();
	Graph(const Graph& orig);
	virtual ~Graph();
	
	void addVertecies(PointVector<>** verts, int length);
	void connect(PointVector<>* a, PointVector<>* b, PointVector<>* c);
	
private:
	typedef std::map<PointVector<>, std::vector<Triangle> (*) > vmap;
	typedef std::vector<Triangle(*)> trivec;
	trivec triangles;
	PointVector<>** vertecies;

};

#endif	/* GRAPH_H */

