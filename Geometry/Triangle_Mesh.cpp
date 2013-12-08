#include <set>
#include <map>
#include <list>
#include <utility>
#include <iostream>
#include <cstdlib>

#include "Triangle_Mesh.h"
#include "Parametric_Surface.h"

using Geometry::Triangle_Mesh;

Triangle_Mesh::Element_map_vector Triangle_Mesh::intersections(Triangle_Mesh a){
	/* Find all elements in this that intersect elements in a */
	// Mapped are all elements that intersect key
	Element_map_vector intersecting_elements;
	for(const Element& e: elem){
		std::vector<Element> intersections;
		for(const Element& ae: a.elem){
			auto collision = e.triangle().intersectionWith(ae.triangle());
			if(collision.first){
				intersections.push_back(e);
			}
		}
		if(intersections.size()){
			intersecting_elements.insert(std::make_pair(e, intersections));
		}
	}	
	return intersecting_elements;
}

void Triangle_Mesh::slice_and_delete(Element_map_vector a){
	
}

long int Triangle_Mesh::size(){
	return elem.size();
}

Triangle_Mesh Triangle_Mesh::get_single_path(Element& begin, Element& end){
	Element_set already_eval;
	Element_set to_be_eval;
	Element_map path_taken;		//mapped element is came from 
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
		for(const auto neighbor: current.second.connected){
			if(neighbor == nullptr)
				continue;
			Element n_neighbor = *elem.find(Element(neighbor));
			int t_g_score = g_score[current.second] +1;
			if(already_eval.find(n_neighbor) != already_eval.end() && t_g_score >= g_score[current.second]){
				continue;
			}
			if(g_score.find(n_neighbor) == g_score.end() || t_g_score < g_score[n_neighbor]){
				path_taken[n_neighbor] = current.second;
				g_score[n_neighbor] = t_g_score;
				f_score.insert(std::make_pair(t_g_score, n_neighbor));
				to_be_eval.insert(n_neighbor);
			}
		}
	}
	throw "FAIL";
}

Triangle_Mesh Triangle_Mesh::construct_mesh(Element end, Element begin, Element_map c){
	Triangle_Mesh result;
	std::list<Element> tmp{end};
	while(tmp.front().tri != begin.tri){
		Element next = c[tmp.front()];
		tmp.front().connected[1] = next.tri;
		next.connected[0] = tmp.front().tri;
		tmp.push_front(next);
	}
	for(Element e: tmp){
		result.elem.insert(e);
	}
	return result;
}

bool Triangle_Mesh::has_element(Triangle_Mesh::Element e) {
	return elem.find(e) != elem.end();
}

bool Triangle_Mesh::element_shares_side(Triangle_Mesh::Element e) {
	for(Element f : elem){
		for(const auto t : f.connected){
			if(t == e.tri){
				return true;
			}
		}
	}
	return false;
}

void Triangle_Mesh::add(Triangle t){
	Element a;
	a.tri = new Triangle{t};
	elem.insert(a);
}

void Triangle_Mesh::add(Triangle& t){
	Element a;
	a.tri = &t;
	elem.insert(a);
}

Triangle_Mesh::Element::Element():
	tri(nullptr),
	connected{nullptr, nullptr, nullptr}
{}

Triangle_Mesh::Element::Element(Triangle* t):
	tri{t},
	connected{nullptr, nullptr, nullptr}
{}

bool Triangle_Mesh::Element::single_valid_connection() const{
	int b = 0;
	for(auto a: Triangle_Mesh::Element::connected){
		if(a != nullptr)
			++b;
	}
	return b==1;
	Triangle_Mesh a;
	for(Triangle b: a){
	
	}
}

bool Triangle_Mesh::Element::connected_with(const Element& e) const{
	for(const Triangle* ptr: connected){
		if(e.tri == ptr)
			return true;
	}
	return false;
}

Geometry::Triangle& Triangle_Mesh::Element::triangle() const{
	return *tri;
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

bool Triangle_Mesh::Iterator::operator!=(Triangle_Mesh::Iterator i) const {
	return it != i.it;
}
