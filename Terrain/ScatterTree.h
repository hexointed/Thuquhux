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
	 *
	 */
	
	class ScatterProp {
	public:
		virtual Gometry::Vector<> segment_pos(double height, double tree_length, int node) = 0; 
		virtual double segment_weight(double height, double tree_length, int node) = 0;
		
		virtual bool continue_node(double, double, int) = 0;
		virtual bool split_node(double, double, int) = 0;
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
		ScatterTree(ScatterProp p);
		
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
	 *
	 */
	
	class ScatterTree::Node{
	public:
		Node();
		Node(Geometry::Vector<> p, double w);
		Node(Geometry::Vector<> p, double w, ScatterProp p);
		
	public:
		Geometry::Vector<> position;
		double weight;
		
		std::unique_ptr<Node*> left, right;
	
	public:
		void regenerate(Node& n);
		void populate(Node& n);
	};
}
#endif /* SCATTERTREE_H */
