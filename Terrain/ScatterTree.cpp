/*
 * File:   ScatterTree.cpp
 * Author: Elias Forsberg
 *
 * Created on March 13, 2014, 8:14 AM
 */

#include "ScatterTree.h"

using namespace Terrain;
using ScatterTree::Node;
using ScatterTree::Iterator;
using ScatterTree::Const_Iterator;

ScatterTree::ScatterTree(ScatterProp& p):
	top_node(*new Node(p)),
	prop(p)
{}

Iterator ScatterTree::begin(){
	return Iterator(top_node);
}

Iterator ScatterTree::end(){
	return Iterator(nullptr, true)
}

/*
 * ScatterTree::Node files below.
 */

Node::Node(ScatterProp& p, int depth, Node* parent):
	position(p.position()),
	weight(p.weight()),
	left(nullptr),
	right(nullptr),
	up(parent)
{
	if(!p.is_end()){
		bool split = p.split();
		p.set_depth(depth+1);
		if(split){
			right = new Node(p, depth+1, this);
		}
		left = new Node(p, depth+1, this);
		p.set_depth(depth);
	}
}

Node::~Node(){
	delete left;
	delete right;
}

bool Node::splits(){
	return right != nullptr && left != nullptr;
}

bool Node::is_end(){
	return left == nullptr;
}

int children(){
	return 1 + (left) ? left->children : 0 + (right) ? right->children : 0;
}

Node& Node::left(){
	if(left == nullptr){
		throw left;
	}
	return *left;
}

Node& Node::right(){
	if(right == nullptr){
		throw right;
	}
	return right;
}

Node& Node::up(){
	if(up == nullptr){
		throw up;
	}
	return up;
}

/*
 * ScatterTree::Iterator methods below.
 */

Iterator::Iterator(Node& n, bool end):
	node(&n),
	is_end(end)
{}

Iterator::Iterator(Node* n, bool end):
	node(n),
	is_end(end)
{}

//NOT DONE
Iterator Iterator::operator++(){
	if(node->is_end){
		node = &node->up();
	}else if(n)
}

Node& Iterator::operator*(){
	return *node;
}

bool Iterator::operator==(Iterator i){
	return node == i.node || (is_end && i.is_end);
}

bool Iterator::operator!=(iterator i){
	return !(*this == i);
}

/*
 * ScatterTree::Const_Iterator metods below.
 */

Const_Iterator::Const_Iterator(const Node&, bool end):
	node(&n),
	is_end(end)
{}

Const_Iterator::Const_Iterator(const Node*, bool end):
	node(n),
	is_end(end)
{}

//NOT DONE
Const_Iterator Const_Iterator::operator++(){

}

Node Const_Iterator::operator*(){
	return *node;
}

bool Const_Iterator::operator==(Iterator i){
	return node == i.node || (is_end && i.is_end);
}

bool Const_Iterator::operator!=(Iterator i){
	return !(*this == i);
}
