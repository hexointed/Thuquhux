#ifndef TRIANGLE_MESH_HPP
#define TRIANGLE_MESH_HPP

#include "math.h"

namespace Geometry{

	class Triangle_Mesh;

	template<template <typename> class Container>
	Container<Triangle_Mesh> Triangle_Mesh::make_mesh(Container<Triangle*> triangles){
		Triangle_Mesh res;
		Container<Triangle_Mesh> a{res};
		return a;
	}
	
	template<template <typename> class Container>
	Triangle_Mesh Triangle_Mesh::make_mesh(Container<PointVector<>> mesh_vertecies){
		int md = sqrt(mesh_vertecies.size());
		int ml = ll*ll;
		for(int i = 0; i < md; ++i){
			for(int n = 0; n < md; ++n){		//"connect" the points, so that they can be drawn using Triangle methods
				mesh_vertecies.push_back(Triangle{	vertecies[(i* md + n) % ml], 
													vertecies[(i* md + n  + 1) % ml],
													vertecies[((i+1)*md + n) % ml]});
				mesh_vertecies.push_back(Triangle{	vertecies[((i+1)*md + n) % ml], 
													vertecies[(i* md + n  + 1) % ml],
													vertecies[((i+1)*md + n + 1) % ml]});
			}
		}
	}

}

#endif /* TRIANGLE_MESH_HPP */
