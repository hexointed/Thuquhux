/* 
 * File:   Triangle_Mesh.cpp
 * Author: Elias Forsberg
 *
 * Created on September 6, 2013, 5:36 PM
 */

#include "Triangle_Mesh.h"

Geometry::Element::Element(Geometry::Triangle t, Triangle_Mesh& universe):
	super(universe)
{
	for(size_t i = 0; i < 3; i++){
		for(size_t j = 0; j < super.vertecies.size(); j++){
			if(t[i].is_eq_comp(super.vertecies[j])){
				vertecies[i] = j;
			}
		}
		super.vertecies.push_back(t[i]);
		vertecies[i] = super.vertecies.size() - 1;
	}
	super.elements.push_back(*this);
}

Geometry::Element::operator Geometry::Triangle (){
	return Geometry::Triangle{super.vertecies[vertecies[0]],
	                          super.vertecies[vertecies[1]],
	                          super.vertecies[vertecies[2]]};
}

Geometry::Triangle_Mesh::Triangle_Mesh(std::vector<Geometry::Triangle> t){
	for(Geometry::Triangle tri : t){
		Geometry::Element(tri, *this);
	}
}

size_t Geometry::Triangle_Mesh::size(){
	return elements.size();
}

void Geometry::Triangle_Mesh::add(Geometry::Triangle t){
	Geometry::Element(t, *this);
}
