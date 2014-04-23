/* 
 * File:   ScatterTree.cpp
 * Author: Elias Forsberg
 *
 * Created on March 13, 2014, 8:14 AM
 */

#include "ScatterTree.h"

using namespace Terrain;
using ScatterTree::Node;

ScatterTree::ScatterTree(ScatterProp p):
	top_node(*new Node(p)),
	prop(p)
{}

/*
 * ScatterTree::Node files below.
 */

Node::Node():
	position(),
	weight(),
	left(nullptr),
	right(nullptr)
{}

Node::Node(Geometry::Vector<> p, double w):
	position(p),
	weight(w),
	left(nullptr),
	right(nullptr)
{}

Node::Node(ScatterProp p){
	position = p.segment_pos();
	weight = p.segment_weight();
	if(p.continue_node()){
		right = new Node(p);
		if(p.split_node()){
			left = new Node(p);
		}
	}
}
