#include <set>
#include <map>
#include <vector>

#include "Triangle_Mesh.h"

using Geometry::Triangle_Mesh;

long int Triangle_Mesh::size(){
	return elem.size();
}

Triangle_Mesh Triangle_Mesh::get_single_path(Element& begin, Element& end){
	std::map<Geometry::Triangle*, Triangle_Mesh::Element> already_eval;
	std::map<int, Triangle_Mesh::Element> to_be_eval;
	std::vector<Triangle_Mesh::Element> path_taken;
	
	auto astarheuristic = [](Element curr, Element goal)->int{return  5;};
	
	to_be_eval.insert(std::make_pair(astarheuristic(begin, end), begin));
	
	while(to_be_eval.size()){
		Element current = to_be_eval.begin()->second;
		to_be_eval.erase(to_be_eval.begin());
		if(true){
			path_taken.push_back(current);
			Triangle_Mesh a{};
			a.elem = path_taken;
			return a;
		}
		already_eval.insert(std::make_pair(current.tri, current));
		for(Element* neighbor: current.connected){
			
		}
	}
	throw "FAIL";
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