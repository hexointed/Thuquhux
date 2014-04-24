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

int ScatterTree::size(){
	return top_node.children();
}

Iterator ScatterTree::begin(){
	return Iterator(top_node);
}

Iterator ScatterTree::end(){
	return Iterator(nullptr);
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
		p.set_parent(*this);
		if(split){
			right = new Node(p, depth+1, this);
		}
		p.set_parent(*this);
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

Iterator::Iterator(Node& n):
	pos(0)
{
	generate(&n);
}

Iterator::Iterator(Node* n):
	pos(0)
{
	generate(n);
	if
}

void Iterator::generate(Node* n){
	if(!n){
		return;
	}
	nodes.push_back(n);
	generate(n->left);
	generate(n->right);
}

Iterator Iterator::operator++(){
	pos++;
	return *this;
}

Iterator Iterator::operator++(int){
	pos++;
	return *this;
}

Iterator Iterator::operator--(){
	pos--;
	return *this;
}

Iterator Iterator::operator--(int){
	pos--;
	return *this;
}

Node& Iterator::operator*(){
	return *(nodes[pos]);
}

bool Iterator::operator==(Iterator i){
	return pos == i.pos && (nodes.sixe() ? nodes[0] == i.nodes[0] : true);
}

bool Iterator::operator!=(iterator i){
	return !(*this == i);
}

/*
 * ScatterTree::Const_Iterator metods below.
 */

Const_Iterator::Const_Iterator(const Node&):
	pos(0)
{
	generate(&n);
}

Const_Iterator::Const_Iterator(const Node*):
	pos(0)
{
	generate(n);
}

void Const_Iterator::generate(const Node* n){
	if(!n){
		return;
	}
	nodes.push_back(n);
	generate(n->left);
	generate(n->right);
}

Const_Iterator Const_Iterator::operator++(){
	pos++;
	return *this;
}

Const_Iterator Const_Iterator::operator++(int){
	pos++;
	return *this;
}

Const_Iterator Const_Iterator::operator--(){
	pos--;
	return *this;
}

Const_Iterator Const_Iterator::operator--(int){
	pos--;
	return *this;
}

Node Const_Iterator::operator*(){
	return *(nodes[pos]);
}

bool Const_Iterator::operator==(Iterator i){
	return pos == i.pos && (nodes.size() ? nodes[0] == i.nodes[0] : true);
}

bool Const_Iterator::operator!=(Iterator i){
	return !(*this == i);
}
