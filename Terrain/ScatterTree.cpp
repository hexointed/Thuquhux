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
	top_node(new Node()),
	prop(p)
{
	generate(*top_node);
	populate(*top_node);
}

void ScatterTree::generate(Node& n){
	n.position = prop.segment()
}

void ScatterTree::populate(Node& n){
	n.left = new Node();
	generate(*n.left);
	n.right = new Node();
	generate(n.right);
}

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
