/* 
 * File:   PointVector.cpp
 * Author: Elias Forsberg
 *
 * Created on December 26, 2012, 4:20 PM
 */

#include "PointVector.h"
#include <math.h>
#include <cassert>

template<const int Dim>
PointVector<Dim>::PointVector(double x, double y, double z){
	assert(Dim >= 3);
    comp[0] = x;
    comp[1] = y;
    comp[2] = z;
}

template<const int Dim>
double PointVector<Dim>::getdx(){
	assert(Dim >= 1);
    return comp[0];
}

template<const int Dim>
double PointVector<Dim>::getdy(){
    assert(Dim >= 2);
    return comp[1];
}

template<const int Dim>
double PointVector<Dim>::getdz(){
    assert(Dim >= 3);
    return comp[2];
}

template<const int Dim>
inline double PointVector<Dim>::getMagnitude(){
	double mag = 0;
	for(int i = 0; i < Dim; i++){
		mag += comp[i] * comp[i];
	}
	return sqrt(mag);
}

template<const int Dim>
double PointVector<Dim>::setdx(double d){
	assert(Dim >= 1);
	comp[0] = d;
}

template<const int Dim>
double PointVector<Dim>::setdy(double d){
	assert(Dim >= 2);
	comp[1] = d;
}

template<const int Dim>
double PointVector<Dim>::setdz(double d){
	assert(Dim >= 3);
	comp[2] = d;
}

template<const int Dim>
PointVector<Dim>* PointVector<Dim>::add(PointVector<Dim>& p){
	for(int i = 0; i < Dim; i++){
		comp[i] += p.comp[i];
	}
	return this;
}

template<const int Dim>
PointVector<Dim>* PointVector<Dim>::sub(PointVector<Dim>& p){
	for(int i = 0; i < Dim; i++){
		comp[i] -= p.comp[i];
	}
	return this;
}

template<const int Dim>
PointVector<Dim>* PointVector<Dim>::mul_comp(PointVector<Dim>& p){
	for(int i = 0; i < Dim; i++){
		comp[i] *= p.comp[i];
	}
	return this;
}

/*template<const int Dim>
PointVector<Dim>* PointVector<Dim>::mul_cross(PointVector<Dim>& p){
	this->dx = this->dy * p.getdz() - this->dz * p.getdy();
	this->dy = this->dz * p.getdx() - this->dx * p.getdz();
	this->dz = this->dx * p.getdy() - this->dy * p.getdx();
	return this;
}*/

template<const int Dim>
PointVector<Dim>* PointVector<Dim>::mul(long double d){
	for(int i = 0; i < Dim; i++){
		comp[i] *= d;
	}
	return this;
}

template<const int Dim>
double PointVector<Dim>::mul_dot(PointVector<Dim>& p, PointVector<Dim>& q){
	double result = 0;
	for(int i = 0; i < Dim; i++){
		result += p.comp[i] * q.comp[i];
	}
	return result;
}

template<const int Dim>
PointVector<Dim>* PointVector<Dim>::div_comp(PointVector<Dim>& p){
    for(int i = 0; i < Dim; i++){
		comp[i] /= p.comp[i];
	}
	return this;
}

template<const int Dim>
PointVector<Dim>* PointVector<Dim>::div(double d){
	for(int i = 0; i < Dim; i++){
		comp[i] /= d;
	}
	return this;
}

template<const int Dim>
PointVector<Dim>* PointVector<Dim>::set_min_comp(PointVector<Dim>& p){
	for(int i = 0; i < Dim; i++){
		*(comp+i) = *(comp+i) < *(p.comp+i) ? *(comp+i) : *(p.comp+i);
	}
	return this;
}

template<const int Dim>
PointVector<Dim>* PointVector<Dim>::set_max_comp(PointVector<Dim>& p){
	for(int i = 0; i < Dim; i++){
		*(comp+i) = *(comp+i) > *(p.comp+i) ? *(comp+i) : *(p.comp+i);
	}
	return this;
}

template<const int Dim>
bool PointVector<Dim>::is_min_comp(PointVector<Dim>& p){
	bool result = true;
	for(int i = 0; i < Dim; i++){
		result = result && comp[i] < p.comp[i];
	}
	return result;
}

template<const int Dim>
bool PointVector<Dim>::is_max_comp(PointVector<Dim>& p){
	bool result = true;
	for(int i = 0; i < Dim; i++){
		result = result && comp[i] > p.comp[i];
	}
	return result;
}