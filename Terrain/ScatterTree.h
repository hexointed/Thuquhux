/*
 * File:   ScatterTree.h
 * Author: Elias Forsberg
 *
 * Created on March 13, 2014, 8:14 AM
 */

#ifndef SCATTERTREE_H
#define SCATTERTREE_H

#include <vector>
#include "../Geometry/Geometry.h"
#include "ScatterProp"

namespace Terrain{
	
	/*
	 * ScatterTree is a binary tree type, which holds a weight and position for each node.
	 * It can be constructed using a ScatterProp object, or by constructing an empty
	 * ScatterTree, and manually adding nodes to it.
	 */
	
	class ScatterTree{
	public:
		class Node;.
		class Iterator;
		class Const_Iterator;
		
	public:
		ScatterTree();
		ScatterTree(ScatterProp& p);
		
		~ScatterTree() = default;
		
	private:
		Node& top_node;
		ScatterProp& prop;
		
	public:
		int size();
		
		Iterator begin();
		Iterator end();
	};
	
	/*
	 * A ScatterTree is made up of connected Nodes. Each node has a position and a weight.
	 */
	
	class ScatterTree::Node{
		friend class ScatterTree;
	private:
		Node(ScatterProp& p, int depth = 0, Node* parent = nullptr);
		
	public:
		Node(const Node&) = delete;
		Node(Node&&) = default;
		
		~Node();
		
	public:
		Geometry::Vector<> position;
		double weight;
		
	private:
		Node* left, right, up;
		
	public:
		Node& operator=(const Node&) = delete;
		Node& operator=(Node&&) = default;
		
		bool splits();	//both right and left valid
		bool is_end();	//neither valid
		bool is_top()	//up valid
		
		int children();
		
		/* These throw nullptr and nullptr if left or right does not exist, respectivly */
		Node& left();
		Node& right();
		Node& up();
	};
	
	/*
	 * ScatterTree::Iterator and ScatterTree::Const_Iterator provide an easy way to iterate
	 * through, deapth first, the Nodes of a ScatterTree;
	 */
	
	class SatterTree::Iterator{
	public:
		Iterator(Node& n);
		Iterator(Node* n);
		
	private:
		void generate(Node* n);
		
	private:
		std::vector<Node*> nodes;
		int pos;
		
	public:
		Iterator operator++();
		Iterator operator++(int);
		Iterator operator--();
		Iterator operator--(int);
		
		Node& operator*();

		bool operator==(Iterator i);
		bool operator!=(Iterator i);
	};
	
	class ScatterTree::Const_Iterator{
	public:
		Const_Iterator(const Node& n);
		Const_Iterator(const Node* n);
		
	private:
		void generate(const Node* n);
		
	private:
		std::vector<const Node*> nodes;
		int pos;
		
	public:
		Const_Iterator operator++();
		Const_Iterator operator++(int);
		Const_Iterator operator--();
		Const_iterator operator--(int);
		
		Node operator*();

		bool operator==(Iterator i);
		bool operator!=(Iterator i);
	};
}
#endif /* SCATTERTREE_H */
