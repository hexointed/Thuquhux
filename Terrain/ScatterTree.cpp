/*
 * File:   ScatterTree.cpp
 * Author: Elias Forsberg
 *
 * Created on March 13, 2014, 8:14 AM
 */

#include "ScatterTree.h"
#include "ScatterProp.h"

using namespace Terrain;

ScatterTree::ScatterTree():
	top_node(*new Node())
{}

ScatterTree::ScatterTree(ScatterProp& p):
	top_node(*new Node(p))
{}

int ScatterTree::size(){
	return top_node.children();
}

ScatterTree::Iterator ScatterTree::begin(){
	return Iterator(top_node);
}

ScatterTree::Iterator ScatterTree::end(){
	return Iterator(nullptr);
}

ScatterTree::Node& ScatterTree::top(){
	return top_node;
}

/*
 * ScatterTree::Node files below.
 */

ScatterTree::Node::Node():
	position({0,0,0}),
	weight(0)
{}

ScatterTree::Node::Node(Geometry::Vector<> p, double w):
	position(p),
	weight(w)
{}

ScatterTree::Node::Node(ScatterProp& p, int depth, Node* parent):
	position(p.position()),
	weight(p.weight()),
	l(nullptr),
	r(nullptr),
	u(parent)
{
	if(!p.is_end()){
		bool split = p.split();
		p.set_depth(depth+1);
		p.set_parent(*this);
		if(split){
			r = new Node(p, depth+1, this);
		}
		p.set_parent(*this);
		l = new Node(p, depth+1, this);
		p.set_depth(depth);
	}
}

ScatterTree::Node::Node(const Node& n):
	position(n.position),
	weight(n.weight)
{
	if(n.l){
		l = new Node(*n.l);
	}
	if(n.r){
		r = new Node(*n.r);
	}
}

ScatterTree::Node::~Node(){
	delete l;
	delete r;
}

bool ScatterTree::Node::splits(){
	return r != nullptr && l != nullptr;
}

bool ScatterTree::Node::is_end(){
	return l == nullptr;
}

int ScatterTree::Node::children(){
	return 1 + (l) ? l->children() : 0 + (r) ? r->children() : 0;
}

ScatterTree::Node& ScatterTree::Node::left(){
	if(l == nullptr){
		throw l;
	}
	return *l;
}

ScatterTree::Node& ScatterTree::Node::right(){
	if(r == nullptr){
		throw r;
	}
	return *r;
}

ScatterTree::Node& ScatterTree::Node::up(){
	if(u == nullptr){
		throw u;
	}
	return *u;
}

void ScatterTree::Node::push_left(Node n){
	if(l){
		throw l;
	}
	l = new Node(n);
}

void ScatterTree::Node::push_right(Node n){
	if(r){
		throw r;
	}
	r = new Node(n);
}

void ScatterTree::Node::erase_left(){
	delete l;
}

void ScatterTree::Node::erase_right(){
	delete r;
}

/*
 * ScatterTree::Iterator methods below.
 */

ScatterTree::Iterator::Iterator(Node& n):
	pos(0)
{
	generate(&n);
}

ScatterTree::Iterator::Iterator(Node* n):
	pos(0)
{
	generate(n);
}

void ScatterTree::Iterator::generate(Node* n){
	if(!n){
		return;
	}
	nodes.push_back(n);
	generate(n->l);
	generate(n->r);
}

ScatterTree::Iterator ScatterTree::Iterator::operator++(){
	pos++;
	return *this;
}

ScatterTree::Iterator ScatterTree::Iterator::operator++(int){
	pos++;
	return *this;
}
ScatterTree::Iterator ScatterTree::Iterator::operator--(){
	pos--;
	return *this;
}

ScatterTree::Iterator ScatterTree::Iterator::operator--(int){
	pos--;
	return *this;
}

ScatterTree::Node& ScatterTree::Iterator::operator*(){
	return *(nodes[pos]);
}

bool ScatterTree::Iterator::operator==(Iterator i){
	return pos == i.pos && (nodes.size() ? nodes[0] == i.nodes[0] : true);
}

bool ScatterTree::Iterator::operator!=(Iterator i){
	return !(*this == i);
}

/*
 * ScatterTree::Const_Iterator metods below.
 */

ScatterTree::Const_Iterator::Const_Iterator(const Node& n):
	pos(0)
{
	generate(&n);
}

ScatterTree::Const_Iterator::Const_Iterator(const Node* n):
	pos(0)
{
	generate(n);
}

void ScatterTree::Const_Iterator::generate(const Node* n){
	if(!n){
		return;
	}
	nodes.push_back(n);
	generate(n->l);
	generate(n->r);
}

ScatterTree::Const_Iterator ScatterTree::Const_Iterator::operator++(){
	pos++;
	return *this;
}

ScatterTree::Const_Iterator ScatterTree::Const_Iterator::operator++(int){
	pos++;
	return *this;
}

ScatterTree::Const_Iterator ScatterTree::Const_Iterator::operator--(){
	pos--;
	return *this;
}

ScatterTree::Const_Iterator ScatterTree::Const_Iterator::operator--(int){
	pos--;
	return *this;
}

ScatterTree::Node ScatterTree::Const_Iterator::operator*(){
	return *(nodes[pos]);
}

bool ScatterTree::Const_Iterator::operator==(Const_Iterator i){
	return pos == i.pos && (nodes.size() ? nodes[0] == i.nodes[0] : true);
}

bool ScatterTree::Const_Iterator::operator!=(Const_Iterator i){
	return !(*this == i);
}
