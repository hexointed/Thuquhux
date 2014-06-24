/*
 * File: ScatterProp.h
 * Author: Elias Forsberg
 *
 * Created on April 24, 2014, 12:50 PM
 */


#ifndef SCATTERPROP_H
#define SCATTERPROP_H

#include "../Geometry/Geometry.h"
#include "ScatterTree.h"
#include <random>

namespace Terrain {
	
	/*
	 * A ScatterProp contains no data and has only virtual member functions. It is intended
	 * to be inherited from by classes describing different types of ScatterTrees. A
	 * ScatterTree is constructed using only a ScatterProp.
	 */
	
	class ScatterProp {
	protected:
		int depth;
		ScatterTree::Node* parent;
		ScatterTree::Node* base;
		
	public:
		virtual Geometry::Vector<> position() = 0;
		virtual double weight() = 0;
		
		virtual bool is_end() = 0;
		virtual bool split() = 0;
		
		virtual void set_depth(int depth);
		virtual void set_parent(ScatterTree::Node& p);
	};
	
	/*
	 * ScatterProps for different types of scatter trees below.
	 */
	
	namespace Scatters {
	
		namespace Trees{
		
			class Acacia : public ScatterProp {
			public:
				Acacia();
				
			private:
				std::normal_distribution<double> distrib;
				
			public:
				virtual Geometry::Vector<> position();
				virtual double weight();
				
				virtual bool is_end();
				virtual bool split();
			};
		}
	}
}

#endif /* SCATTERPROP_H */
