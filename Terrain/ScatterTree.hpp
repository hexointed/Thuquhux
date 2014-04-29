/*
 * File ScatterTree.hpp
 * Author: Elias Forsberg
 *
 * Created on: April 29, 2014,  10:48 AM
 */

#ifndef SCATTERTREE_HPP
#define SCATTERTREE_HPP

template<typename Functor>
void Terrain::ScatterTree::Node::foreach(Functor f){
	if(l){
		l->foreach(f);
	}
	if(r){
		r->foreach(f);
	}
}

template<typename Functor>
void Terrain::ScatterTree::foreach(Functor f){
	top_node.foreach(f);
}

#endif /* SCATTERTREE_HPP */
