/* 
 * File:   ScatterTree.h
 * Author: Elias Forsberg
 *
 * Created on March 13, 2014, 8:14 AM
 */

#ifndef SCATTERTREE_H
#define SCATTERTREE_H

#include "../Geometry/Geometry.h"

namespace Terrain{
	class ScatterProp {
		virtual Gometry::Vector<> segment(double height, double tree_length, int node) = 0; 
		virtual double segment_weight(double height, double tree_length, int node) = 0;
		
		virtual bool continue_node(double, double, int) = 0;
		virtual bool split_node(double, double, int) = 0;
	};
	
	class ScatterTree{
		
	}
}
#endif /* SCATTERTREE_H */
