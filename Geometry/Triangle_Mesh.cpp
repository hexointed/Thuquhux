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
		for(size_t j = 0; j < super._vertecies.size(); j++){
			if(t[i].is_eq_comp(super._vertecies[j])){
				vertecies[i] = j;
			}
		}
		super._vertecies.push_back(t[i]);
		vertecies[i] = super._vertecies.size() - 1;
	}
	super.elements.push_back(*this);
}

Geometry::Element::operator Geometry::Triangle () const{
	return Geometry::Triangle{super._vertecies[vertecies[0]],
	                          super._vertecies[vertecies[1]],
	                          super._vertecies[vertecies[2]]};
}

Geometry::Triangle_Mesh::Triangle_Mesh(const Triangle_Mesh& orig)
{
	for(Triangle t : orig.all_triangles()){
		Geometry::Element(t, *this);
	}
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

std::vector<Geometry::Triangle> Geometry::Triangle_Mesh::all_triangles() const {
	std::vector<Geometry::Triangle> result;
	for(const Geometry::Triangle t : elements){
		result.push_back(t);
	}
	return result;
}

std::vector<Geometry::Triangle> Geometry::Triangle_Mesh::intersecting_triangles(Geometry::Triangle with){
	std::vector<Geometry::Triangle> result;
	for(Geometry::Triangle t : elements){
		if(with.intersectionWith(t).first){
			result.push_back(t);
		}
	}
	return result;
}
