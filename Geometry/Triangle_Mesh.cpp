#include <set>
#include <map>
#include <utility>

#include "Triangle_Mesh.h"

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
		auto& current = (*f_score.begin());
		to_be_eval.erase(to_be_eval.begin());
		if(current.second.tri == end.tri){
			return construct_mesh(end, path_taken);
		}
		already_eval.insert(current.second);
		for(Element* neighbor: current.second.connected){
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

Triangle_Mesh Triangle_Mesh::construct_mesh(Element a, std::map<Element,Element,Element::Elementcompare> b){
	Triangle_Mesh result;
	Element current = a;
	do{
		if(result.elem.size()){
			result.elem.back().connected[0] = &current;
			result.elem.back().connected[1]	= nullptr;
			result.elem.back().connected[2]	= nullptr;
		}
		result.elem.push_back(current);
		Element tmp = current;
		current = b[current];
		b.erase(tmp);
	}while(b.size());
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

bool Triangle_Mesh::Element::single_valid_connection(){
	int b = 0;
	for(Triangle_Mesh::Element* a: Triangle_Mesh::Element::connected){
		if(a != nullptr)
			++b;
	}
	return b==1;
}