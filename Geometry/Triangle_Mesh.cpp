#include <set>
#include <map>
#include <utility>
#include <iostream>
#include <cstdlib>

#include "Triangle_Mesh.h"
#include "Parametric_Surface.h"

using Geometry::Triangle_Mesh;

long int Triangle_Mesh::size(){
	return elem.size();
}

Triangle_Mesh Triangle_Mesh::get_single_path(Element& begin, Element& end){
	std::set<Triangle_Mesh::Element, Element::Elementcompare> already_eval;
	std::set<Triangle_Mesh::Element, Element::Elementcompare> to_be_eval;
	std::map<Triangle_Mesh::Element, Triangle_Mesh::Element/*Came from*/, Element::Elementcompare> path_taken;
	std::map<Element, int, Element::Elementcompare> g_score;
	std::map<int, Element> f_score;
	
	to_be_eval.insert(begin);
	g_score.insert(std::make_pair(begin, 0));
	f_score.insert(std::make_pair(1, begin));
	
	while(to_be_eval.size()){
		auto current = (*f_score.begin());
		to_be_eval.erase(to_be_eval.begin());
		f_score.erase(f_score.begin());
		if(current.second.tri == end.tri){
			return construct_mesh(end, begin, path_taken);
		}
		already_eval.insert(current.second);
		for(Element* neighbor: current.second.connected){
			if(neighbor == nullptr)
				continue;
			int t_g_score = g_score[current.second] +1;
			if(already_eval.find(*neighbor) != already_eval.end() && t_g_score >= g_score[current.second]){
				continue;
			}
			if(g_score.find(*neighbor) == g_score.end() || t_g_score < g_score[*neighbor]){
				path_taken[*neighbor] = current.second;
				g_score[*neighbor] = t_g_score;
				f_score.insert(std::make_pair(t_g_score, *neighbor));
				to_be_eval.insert(*neighbor);
			}
		}
	}
	throw "FAIL";
}

Triangle_Mesh Triangle_Mesh::construct_mesh(Element end, Element begin, std::map<Element,Element,Element::Elementcompare> c){
	Triangle_Mesh result;
	Element current = end;
	while(current.tri != begin.tri){
		result.elem.push_back(current);
		current = c[current];
	}
	result.elem.push_back(current);
	
	for(unsigned int i = 0; i < result.elem.size(); i++){
		if(i > 0)
			result.elem[i].connected[0] = &result.elem[i-1];
		if(i < result.elem.size())
			result.elem[0].connected[1] = &result.elem[i+1];
		result.elem[0].connected[2] = nullptr;
	}
	return result;
}

bool Triangle_Mesh::is_loop(){
	Triangle_Mesh::Element* e = &elem[0];
	for(Triangle_Mesh::Element& a: elem){
		if(!a.single_valid_connection())
			return false;
		e = &a;
	}
	return e == &elem[0];
}

void Triangle_Mesh::add(Triangle t){
	Element a;
	a.tri = new Triangle{t};
	elem.push_back(a);
}

void Triangle_Mesh::add(Triangle& t){
	Element a;
	a.tri = &t;
	elem.push_back(a);
}

Triangle_Mesh::Element::Element():
	tri(nullptr),
	connected{nullptr, nullptr, nullptr}
{}

bool Triangle_Mesh::Element::single_valid_connection(){
	int b = 0;
	for(Triangle_Mesh::Element* a: Triangle_Mesh::Element::connected){
		if(a != nullptr)
			++b;
	}
	return b==1;
	Triangle_Mesh a;
	for(Triangle b: a){
	
	}
}

Geometry::Triangle& Triangle_Mesh::Iterator::operator *(){
	return *(*it).tri;
}

Triangle_Mesh::Iterator Triangle_Mesh::Iterator::operator++(){
	++it;
	return *this;
}

Triangle_Mesh::Iterator Triangle_Mesh::Iterator::operator++(int){
	it++;
	return *this;
}

Triangle_Mesh::Iterator Triangle_Mesh::Iterator::operator--(){
	--it;
	return *this;
}

Triangle_Mesh::Iterator Triangle_Mesh::Iterator::operator--(int){
	it--;
	return *this;
}

Triangle_Mesh::Iterator Triangle_Mesh::Iterator::operator +(int p) const {
	return Triangle_Mesh::Iterator{it + p};
}

Triangle_Mesh::Iterator Triangle_Mesh::Iterator::operator -(int p) const {
	return Triangle_Mesh::Iterator{it - p};
}

int Triangle_Mesh::Iterator::operator -(Triangle_Mesh::Iterator i) const {
	return it - i.it;
}

bool Triangle_Mesh::Iterator::operator!=(Triangle_Mesh::Iterator i) const {
	return it != i.it;
}
