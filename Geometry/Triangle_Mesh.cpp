#include <set>

#include "Triangle_Mesh.h"

using Geometry::Triangle_Mesh;

long int Triangle_Mesh::size(){
	return elem.size();
}

Triangle_Mesh Triangle_Mesh::get_single_path(Element& begin, Element& end){
	std::set<Triangle_Mesh::Element*> already_tried;
	std::vector<Element> path;
	Element* current = &begin;
	while(true){
		for(Triangle_Mesh::Element* a: current->connected){
			if(a == nullptr)
				continue;
			if(current = &end){
				path.push_back(*current);
			}
			
		}
	}
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