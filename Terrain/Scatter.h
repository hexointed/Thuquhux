/*
 * File Scatter.h
 * Author: Elias Forsberg
 *
 * Created on April 26, 2014, 3:17 PM
 *
 * Functions for turning ScatterTrees into useful meshes are locaded in this file.
 * Each type of scatter requires its own mesh-creating function.
 */

#ifndef SCATTER_H
#define SCATTER_H

#include "ScatterTree.h"
#include "../Geometry/Triangle_Mesh.h"
#include "../Physics/PhysObject.h"

namespace Terrain{
	class Scatter : public Physics::PhysObject {
	public:
		Scatter(Scatters::ScatterProp& p);
		
	private:
		
	public:
		
	};
}

#endif /* SCATTER_H */
