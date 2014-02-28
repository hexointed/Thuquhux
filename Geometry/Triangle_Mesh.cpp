/* 
 * File:   Triangle_Mesh.cpp
 * Author: Elias Forsberg
 *
 * Created on September 6, 2013, 5:36 PM
 */

#include "Triangle_Mesh.h"

using Geometry::Triangle;
using Geometry::Triangle_Mesh;

Triangle_Mesh::Triangle_Mesh(std::vector<Geometry::Vector<>> p):
	vertex{p}
{
	index.reserve(vertex.size());
	for(size_t i = 0; i < vertex.size(); i++){
		index.push_back(i);
	}
}

Triangle_Mesh::Triangle_Mesh(std::vector<Geometry::Vector<>> p, std::vector<int> i):
	vertex{p},
	index{i}
{}

size_t Triangle_Mesh::size() const{
	return index.size() - 2;
}

void Triangle_Mesh::add(std::vector<Geometry::Vector<>> p){
	Triangle_Mesh a(p);
	add(a);
}

void Triangle_Mesh::add(const Triangle_Mesh& t){
	std::vector<int> i = t.index;
	for(int& it : i){
		it += vertex.size();
	}
	index.reserve(index.size() + i.size());
	index.insert(index.end(), i.begin(), i.end());
	
	vertex.reserve(vertex.size() + t.vertex.size());
	vertex.insert(vertex.end(), t.vertex.begin(), t.vertex.end());
}

std::vector<Triangle> Triangle_Mesh::all_triangles(){
	std::vector<Triangle> result;
	for(Triangle t : *this){
		result.push_back(t);
	}
	return result;
}

std::vector<Triangle> Triangle_Mesh::intersecting_triangles(Triangle with){
	std::vector<Triangle> result;
	for(Triangle t : *this){
		if(with.intersectionWith(t).first){
			result.push_back(t);
		}
	}
	return result;
}

Triangle_Mesh::Iterator Triangle_Mesh::begin(){
	return Iterator(*this, 0);
}

Triangle_Mesh::Iterator Triangle_Mesh::end(){
	return Iterator(*this, size());
}

/* All methods in Triangle_Mesh::Element are located below */

Triangle_Mesh::Element::Element(Triangle_Mesh& s, int a, int b, int c):
	vertecies{a,b,c},
	super{s}
{}

Triangle_Mesh::Element::operator Geometry::Triangle () const{
	return Geometry::Triangle{super.vertex[super.index[vertecies[0]]],
	                          super.vertex[super.index[vertecies[1]]],
	                          super.vertex[super.index[vertecies[2]]]};
}

Geometry::Vector<>& Triangle_Mesh::Element::operator[](int i){
	return super.vertex[super.index[vertecies[i]]];
}

/* All methods in Triangle_Mesh::Iterator are located below */

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
	return Element(super, pos, pos+1, pos+2);
}

const Triangle_Mesh::Element Triangle_Mesh::Iterator::operator *() const{
	return Element(super, pos, pos+1, pos+2);
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

Triangle_Mesh::Iterator Triangle_Mesh::Iterator::operator +(int i) const{
	return Iterator(super, pos + i);
}

Triangle_Mesh::Iterator Triangle_Mesh::Iterator::operator -(int i) const{
	return Iterator(super, pos - i);
}

int Triangle_Mesh::Iterator::operator -(Triangle_Mesh::Iterator i) const{
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
