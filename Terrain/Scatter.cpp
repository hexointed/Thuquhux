/*
 * File Scatter.cpp
 * Author: Elias Forsberg
 *
 * Created on April 25, 2014, 4:12 PM
 *
 * Functions for turning ScatterTrees into useful meshes are located in this file.
 * Each type of scatter requires its own mesh-creating function.
 */

#include "ScatterTree.h"
#include "../Geometry/Triangle_Mesh.h"
#include "ScatterTree.h"
#include "ScatterProp.h"

using namespace Terrain;

Scatter::Scatter(Scatters::ScatterProp& p){
	ScatterTree tree{p};
	
}
