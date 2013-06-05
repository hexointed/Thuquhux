/* 
 * File:   PointVector.cpp
 * Author: Elias Forsberg
 *
 * Created on December 26, 2012, 4:20 PM
 */

#ifndef POINTVECTOR_CPP
#define POINTVECTOR_CPP

#include "PointVector.h"
#include <math.h>
#include <cassert>

template<unsigned int Dim>
PointVector<Dim>::PointVector():
	comp {}
{}

template<unsigned int Dim>
PointVector<Dim>::PointVector(double composants[Dim]){
	std::copy(composants, composants+Dim, comp);
}

template<unsigned int Dim>
template<unsigned int D2>
PointVector<Dim>::PointVector(PointVector<D2> orig):
	comp {}
{
	constexpr int m = std::min(Dim, D2);
	std::copy(orig.comp, orig.comp + m, comp);
}

template<unsigned int Dim>
template<typename... Tail>
PointVector<Dim>::PointVector(Tail... t){
	PointVector();
	pconstruct(0, t...);
}

template<unsigned int Dim>
template<typename First, typename... Tail>
inline void PointVector<Dim>::pconstruct(int i, First f, Tail... t){
	comp[i] = f;
	pconstruct(i+1, t...);
}

template<unsigned int Dim>
inline void PointVector<Dim>::pconstruct(int i){}

template<unsigned int Dim>
double PointVector<Dim>::get(int i) const{
	assert(i <= Dim);
	return comp[i];
}

template<unsigned int Dim>
double PointVector<Dim>::getdx() const{
	assert(Dim >= 1);
    return comp[0];
}

template<unsigned int Dim>
double PointVector<Dim>::getdy() const{
    assert(Dim >= 2);
    return comp[1];
}

template<unsigned int Dim>
double PointVector<Dim>::getdz() const{
    assert(Dim >= 3);
    return comp[2];
}

template<unsigned int Dim>
double PointVector<Dim>::getMagnitude() const{
	double mag = 0;
	for(int i = 0; i < Dim; i++){
		mag += comp[i] * comp[i];
	}
	return sqrt(mag);
}

template<unsigned int Dim>
double PointVector<Dim>::sum_comp() const{
	double sum = 0;
	for(auto x : comp){
		sum += x;
	}
	return sum;
}

template<unsigned int Dim>
void PointVector<Dim>::set(int i, double d){
	assert(i <= Dim);
	comp[i] = d;
}

template<unsigned int Dim>
void PointVector<Dim>::setdx(double d){
	assert(Dim >= 1);
	comp[0] = d;
}

template<unsigned int Dim>
void PointVector<Dim>::setdy(double d){
	assert(Dim >= 2);
	comp[1] = d;
}

template<unsigned int Dim>
void PointVector<Dim>::setdz(double d){
	assert(Dim >= 3);
	comp[2] = d;
}

template<unsigned int Dim>
PointVector<Dim>& PointVector<Dim>::add(PointVector<Dim> p){
	for(int i = 0; i < Dim; i++){
		comp[i] += p.comp[i];
	}
	return *this;
}

template<unsigned int Dim>
PointVector<Dim>& PointVector<Dim>::sub(PointVector<Dim> p){
	for(int i = 0; i < Dim; i++){
		comp[i] -= p.comp[i];
	}
	return *this;
}

template<unsigned int Dim>
PointVector<Dim> PointVector<Dim>::add(PointVector<Dim> p, PointVector<Dim> q){
	return p.add(q);
}

template<unsigned int Dim>
PointVector<Dim> PointVector<Dim>::sub(PointVector<Dim> p, PointVector<Dim> q){
	return p.sub(q);
}

template<unsigned int Dim>
PointVector<Dim>& PointVector<Dim>::mul_comp(PointVector<Dim> p){
	for(int i = 0; i < Dim; i++){
		comp[i] *= p.comp[i];
	}
	return *this;
}

template<unsigned int Dim>
PointVector<Dim>& PointVector<Dim>::mul_cross(PointVector<Dim> p){
	return *this;
}

template<>
inline PointVector<3>& PointVector<3>::mul_cross(PointVector<3> p){
	PointVector<3> q(*this);
	comp[0] = q.comp[1] * p.comp[2] - q.comp[2] * p.comp[1];
	comp[1] = q.comp[2] * p.comp[0] - q.comp[0] * p.comp[2];
	comp[2] = q.comp[0] * p.comp[1] - q.comp[1] * p.comp[0];
	return *this;
}

template<>
inline PointVector<7>& PointVector<7>::mul_cross(PointVector<7> p){
	PointVector<7> q(*this);
	comp[0] = q.comp[1] * p.comp[3] - q.comp[3] * p.comp[1] + q.comp[2] * p.comp[6] - q.comp[6] * p.comp[2] + q.comp[4] * p.comp[5] - q.comp[5] * p.comp[4];
	comp[1] = q.comp[2] * p.comp[4] - q.comp[4] * p.comp[2] + q.comp[3] * p.comp[0] - q.comp[0] * p.comp[3] + q.comp[5] * p.comp[6] - q.comp[6] * p.comp[5];
	comp[2] = q.comp[3] * p.comp[5] - q.comp[5] * p.comp[3] + q.comp[4] * p.comp[1] - q.comp[1] * p.comp[4] + q.comp[6] * p.comp[0] - q.comp[0] * p.comp[6];
	comp[3] = q.comp[4] * p.comp[6] - q.comp[6] * p.comp[4] + q.comp[5] * p.comp[2] - q.comp[2] * p.comp[5] + q.comp[0] * p.comp[1] - q.comp[1] * p.comp[0];
	comp[4] = q.comp[5] * p.comp[0] - q.comp[0] * p.comp[5] + q.comp[6] * p.comp[3] - q.comp[3] * p.comp[6] + q.comp[1] * p.comp[2] - q.comp[2] * p.comp[1];
	comp[5] = q.comp[6] * p.comp[1] - q.comp[1] * p.comp[6] + q.comp[0] * p.comp[4] - q.comp[4] * p.comp[0] + q.comp[2] * p.comp[3] - q.comp[3] * p.comp[2];
	comp[6] = q.comp[0] * p.comp[2] - q.comp[2] * p.comp[0] + q.comp[1] * p.comp[5] - q.comp[5] * p.comp[1] + q.comp[3] * p.comp[4] - q.comp[4] * p.comp[3];
	return *this;
}

template<unsigned int Dim>
PointVector<Dim>& PointVector<Dim>::mul(long double d){
	for(int i = 0; i < Dim; i++){
		comp[i] *= d;
	}
	return *this;
}

template<unsigned int Dim>
double PointVector<Dim>::mul_dot(PointVector<Dim> p, PointVector<Dim> q){
	double result = 0;
	for(int i = 0; i < Dim; i++){
		result += p.comp[i] * q.comp[i];
	}
	return result;
}

template<unsigned int Dim>
PointVector<Dim> PointVector<Dim>::mul_comp(PointVector<Dim> p, PointVector<Dim> q){
	return p.mul_comp(q);
}

template<unsigned int Dim>
PointVector<Dim> PointVector<Dim>::mul_cross(PointVector<Dim> p, PointVector<Dim> q){
	return p.mul_cross(q);
}

template<unsigned int Dim>
PointVector<Dim> PointVector<Dim>::mul(double d, PointVector<Dim> p){
	return p.mul(d);
}

template<unsigned int Dim>
PointVector<Dim>& PointVector<Dim>::div_comp(PointVector<Dim> p){
    for(int i = 0; i < Dim; i++){
		comp[i] /= p.comp[i];
	}
	return *this;
}

template<unsigned int Dim>
PointVector<Dim>& PointVector<Dim>::div(double d){
	for(int i = 0; i < Dim; i++){
		comp[i] /= d;
	}
	return *this;
}

template<unsigned int Dim>
PointVector<Dim> PointVector<Dim>::div_comp(PointVector<Dim> p, PointVector<Dim> q){
	return p.div_comp(q);
}

template<unsigned int Dim>
PointVector<Dim> PointVector<Dim>::div(double d, PointVector p){
	return p.div(d);
}

template<unsigned int Dim>
PointVector<Dim>& PointVector<Dim>::pow(double d){
	for(int i = 0; i < Dim; i++){
		comp[i] = pow(comp[i], d);
	}
	return *this;
}

template<unsigned int Dim>
PointVector<Dim>& PointVector<Dim>::pow_comp(PointVector p){
	for(int i = 0; i < Dim; i++){
		comp[i] = pow(comp[i], p.comp[i]);
	}
}

template<unsigned int Dim>
PointVector<Dim> PointVector<Dim>::pow(double d, PointVector p){
	return p.pow(d);
}

template<unsigned int Dim>
PointVector<Dim> PointVector<Dim>::pow_comp(PointVector p, PointVector q){
	return p.pow_comp(q);
}

template<unsigned int Dim>
PointVector<Dim>& PointVector<Dim>::set_min_comp(PointVector<Dim> p){
	for(int i = 0; i < Dim; i++){
		*(comp+i) = *(comp+i) < *(p.comp+i) ? *(comp+i) : *(p.comp+i);
	}
	return *this;
}

template<unsigned int Dim>
PointVector<Dim>& PointVector<Dim>::set_max_comp(PointVector<Dim> p){
	for(int i = 0; i < Dim; i++){
		*(comp+i) = *(comp+i) > *(p.comp+i) ? *(comp+i) : *(p.comp+i);
	}
	return *this;
}

template<unsigned int Dim>
PointVector<Dim> PointVector<Dim>::min_comp(PointVector p, PointVector q){
	return p.set_min_comp(q);
}

template<unsigned int Dim>
PointVector<Dim> PointVector<Dim>::max_comp(PointVector p, PointVector q){
	return p.set_max_comp(q);
}

template<unsigned int Dim>
bool PointVector<Dim>::is_min_comp(PointVector<Dim> p) const{
	for(int i = 0; i < Dim; i++){
		if(comp[i] > p.comp[i])
			return false;
	}
	return true;
}

template<unsigned int Dim>
bool PointVector<Dim>::is_max_comp(PointVector<Dim> p) const{
	for(int i = 0; i < Dim; i++){
		if(comp[i] < p.comp[i])
			return false;
	}
	return true;
}

template<unsigned int Dim>
bool PointVector<Dim>::is_eq_comp(PointVector<Dim> p) const{
	for(int i = 0; i < Dim; i++){
		if(comp[i] != p.comp[i])
			return false;
	}
	return true;
}

template<unsigned int Dim>
PointVector<Dim>& PointVector<Dim>::make_unit(){
	double mag = getMagnitude();
	for(int i = 0; i < Dim; i++){
		comp[i] /= mag; 
	}
	return *this;
}

template<unsigned int Dim>
PointVector<Dim> PointVector<Dim>::make_unit(PointVector<Dim> p){
	return p.make_unit();
}

template<unsigned int Dim>
PointVector<Dim>& PointVector<Dim>::project(PointVector p){
	mul_comp(p);
	PointVector q(p);
	q.mul_comp(p);
	double d = q.sum_comp();
	double e = sum_comp();
	for(int i = 0; i < Dim; i++){
		comp[i] = p.comp[i] * e / d;
	}
	return *this;
}

template<unsigned int Dim>
PointVector<Dim> PointVector<Dim>::project(PointVector p, PointVector q){
	return p.project(q);
}

template<unsigned int Dim>
double PointVector<Dim>::taxicab_distance(PointVector p, PointVector q){
	double res;
	for(int i = 0; i < Dim; i++){
		res += abs(p.comp[i] - q.comp[i]);
	}
	return res;
}

template<unsigned int Dim>
std::array<bool, Dim> PointVector<Dim>::operator ==(PointVector<Dim> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] == p.comp[i];
	}
	return result;
}

template<unsigned int Dim>
std::array<bool, Dim> PointVector<Dim>::operator !=(PointVector<Dim> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] != p.comp[i];
	}
	return result;
}

template<unsigned int Dim>
std::array<bool, Dim> PointVector<Dim>::operator >(PointVector<Dim> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] > p.comp[i];
	}
	return result;
}

template<unsigned int Dim>
std::array<bool, Dim> PointVector<Dim>::operator <(PointVector<Dim> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] < p.comp[i];
	}
	return result;
}

template<unsigned int Dim>
std::array<bool, Dim> PointVector<Dim>::operator >=(PointVector<Dim> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] >= p.comp[i];
	}
	return result;
}

template<unsigned int Dim>
std::array<bool, Dim> PointVector<Dim>::operator <=(PointVector<Dim> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] <= p.comp[i];
	}
	return result;
}

template<unsigned int Dim>
bool Boolarr::all(std::array<bool,Dim> a){
	for(int i = 0; i < Dim; i++){
		if(!a[i]){
			return false;
		}
	}
	return true;
}

template<unsigned int Dim>
bool Boolarr::any(std::array<bool,Dim> a){
	for(int i = 0; i < Dim; i++){
		if(a[i]){
			return true;
		}
	}
	return false;
}

template<unsigned int Dim>
bool Boolarr::most(std::array<bool,Dim> a){
	int temp = 0;
	for(int i = 0; i < Dim; i++){
		if(a[i]){
			temp++;
		}
	}
	return temp >= Dim/2.0;
}

#endif /*POINTVECTOR_CPP*/