/* 
 * File:   Triangle_Mesh.cpp
 * Author: Elias Forsberg
 *
 * Created on September 6, 2013, 5:36 PM
 */

#include "Triangle_Mesh.h"

using Geometry::Triangle;
using Geometry::Element;
using Geometry::Triangle_Mesh;

Element::Element(Triangle t, Triangle_Mesh& universe):
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

Element::operator Triangle () const{
	return Triangle{super._vertecies[vertecies[0]],
	                          super._vertecies[vertecies[1]],
	                          super._vertecies[vertecies[2]]};
}

Triangle_Mesh::Triangle_Mesh(const Triangle_Mesh& orig)
{
	for(Triangle t : orig.all_triangles()){
		Element(t, *this);
	}
}

Triangle_Mesh::Triangle_Mesh(std::vector<Triangle> t){
	for(Triangle tri : t){
		Element(tri, *this);
	}
}

Triangle_Mesh& Triangle_Mesh::operator=(const Triangle_Mesh& orig){
	elements.clear();
	_vertecies.clear();
	for(Triangle tri : orig){
		Element(tri, *this);
	}
	return *this;
}

size_t Triangle_Mesh::size(){
	return elements.size();
}

void Triangle_Mesh::add(Triangle t){
	Element(t, *this);
}

std::vector<Triangle> Triangle_Mesh::all_triangles() const {
	std::vector<Triangle> result;
	for(const Triangle t : elements){
		result.push_back(t);
	}
	return result;
}

std::vector<Triangle> Triangle_Mesh::intersecting_triangles(Triangle with){
	std::vector<Triangle> result;
	for(Triangle t : elements){
		if(with.intersectionWith(t).first){
			result.push_back(t);
		}
	}
	return result;
}

/* Triangle_Mesh::Iterator */

Triangle_Mesh::Iterator::Iterator(Triangle_Mesh& s, int p):
	super{s},
	pos{p}
{}

bool Triangle_Mesh::Iterator::operator==(Iterator i) const{
	return (pos == i.pos) && (&super == &i.super);
}

bool Triangle_Mesh::Iterator::operator!=(Iterator i) const{
	return (pos != i.pos) || (&super != &i.super);
}

bool Triangle_Mesh::Iterator::operator <(Iterator i) const{
	return (pos < i.pos) && (&super == &i.super);
}

bool Triangle_Mesh::Iterator::operator >(Iterator i) const{
	return (pos > i.pos) && (&super == &i.super);
}

bool Triangle_Mesh::Iterator::operator<=(Iterator i) const{
	return (pos <= i.pos) && (&super == &i.super);
}

bool Triangle_Mesh::Iterator::operator>=(Iterator i) const{
	return (pos >= i.pos) && (&super == &i.super);
}

Triangle_Mesh::Element Triangle_Mesh::Iterator::operator *(){
	int v01 = int(pos/2.0) % super.width;
	int v2  = (int(pos/2) == int(pos/2.0 + 0.5)) ? v01 : v01 + super.width + 1;
	return Element(super, v01 + 1, v01 + super.width, v2);
}

const Element Triangle_Mesh::Iterator::operator *() const{
	int v01 = int(pos/2.0) % super.width;
	int v2  = (int(pos/2) == int(pos/2.0 + 0.5)) ? v01 : v01 + super.width + 1;
	return Element(super, v01 + 1, v01 + super.width, v2);
}

void Triangle_Mesh::Iterator::operator++(){
	pos++;
}

void Triangle_Mesh::Iterator::operator++(int){
	pos++;
}

void Triangle_Mesh::Iterator::operator--(){
	pos--;
}

void Triangle_Mesh::Iterator::operator--(int){
	pos--;
}

Triangle_Mesh::Iterator Triangle_Mesh::Iterator::operator +(int i){
	return Iterator(super, pos + i);
}

Triangle_Mesh::Iterator Triangle_Mesh::Iterator::operator -(int i){
	return Iterator(super, pos - i);
}

int Triangle_Mesh::Iteator::operator -(Triangle_Mesh::Iterator i){
	return pos - i.pos;
}

Triangle_Mesh::Element Triangle_Mesh::Iterator::operator[](int i){
	Iterator a(super, pos + i);
	return *a;
}

const Triangle_Mesh::Element Triangle_Mesh::Iterator::operator[](int i) const{
	Iterator a(super, pos + i);
	return *a;
}
