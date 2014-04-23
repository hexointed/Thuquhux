/*
 * File:   ScatterTree.h
 * Author: Elias Forsberg
 *
 * Created on March 13, 2014, 8:14 AM
 */

#ifndef SCATTERTREE_H
#define SCATTERTREE_H

#include <memory>
#include "../Geometry/Geometry.h"

namespace Terrain{
	
	/*
	 * A ScatterProp contains no data and has only virtual member functions. It is intended
	 * to be inherited from by classes describing different types of ScatterTrees. A
	 * ScatterTree is constructed using only a ScatterProp.
	 */
	
	class ScatterProp {
	public:
		virtual Gometry::Vector<> position() = 0;
		virtual double weight() = 0;
		
		virtual bool is_end() = 0;
		virtual bool split() = 0;
		
		virtual void set_depth(int depth) = 0;
	};
	
	/*
	 * ScatterTree is a binary tree type, which holds a weight and position for each node.
	 * It can be constructed using a ScatterProp object, or by constructing an empty
	 * ScatterTree, and manually adding nodes to it.
	 */
	
	class ScatterTree{
	private:
		class Node;
		
	public:
		class Iterator;
		class Const_Iterator;
		
	public:
		ScatterTree();
		ScatterTree(ScatterProp& p);
		
		~ScatterTree() = default;
		
	private:
		Node& top_noade;
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
	public:
		Node(ScatterProp& p, int depth = 0, Node* parent = nullptr);
		~Node();
	public:
		Geometry::Vector<> position;
		double weight;
	private:
		Node* left, right, up;
	public:
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
		Iterator(Node& n, bool is_end = false);
		Iterator(Node* n, bool is_end);
	private:
		Node* node;
		bool is_end;
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
		Const_Iterator(const Node& n, bool is_end = false);
		Const_Iterator(const Node*, bool is_end);
	private:
		const Node* node;
		bool is_end;
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
