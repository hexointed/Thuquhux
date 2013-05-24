/* 
 * File:   Triangle.cpp
 * Author: elias
 * 
 * Created on May 23, 2013, 7:11 PM
 */

#include "Geometry.h"

using namespace Geometry;

template<const int Sides, const int Dim>
Polygon<Sides, Dim>::Polygon(){
}

template<const int Sides, const int Dim>
Polygon<Sides, Dim>::Polygon(PointVector<Dim>* sides){
	for(int i = 0; i < Sides; i++){
		this->vertecies[i] = sides[i];
	}
}

template<const int Sides, const int Dim>
Polygon<Sides, Dim>::Polygon(const Polygon<Sides,Dim>& orig){
	for(int i = 0; i < Sides; i++){
		this->vertecies[i] = orig[i];
	}
}

template<const int Sides, const int Dim>
Polygon<Sides, Dim>::~Polygon(){
}

Triangle::Triangle() {
}

Triangle::Triangle(const Triangle& orig) {
}

Triangle::~Triangle() {
}

bool Triangle::passesThrough(PointVector<>& max, PointVector<>& min){
	bool result = true;
	PointVector<> d[3] = {vertecies[0], vertecies[1], vertecies[2]};
	for(int i = 0; i < 3; i++){
		d[i].mul_comp(d[i]);
		
	}
	return result;
}