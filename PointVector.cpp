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

template<const int Dim>
PointVector<Dim>::PointVector(){
	for(int i = 0; i < Dim; i++){
		comp[i] = 0;
	}
}

template<const int Dim>
PointVector<Dim>::PointVector(double composants[Dim]){
	for(int i = 0; i < Dim; i++){
		comp[i] = composants[i];
	}
}

template<const int Dim>
template<typename... Tail>
PointVector<Dim>::PointVector(Tail... t){
	PointVector();
	pconstruct(0, t...);
}

template<const int Dim>
template<typename First, typename... Tail>
inline void PointVector<Dim>::pconstruct(int i, First f, Tail... t){
	comp[i] = f;
	pconstruct(i+1, t...);
}

template<const int Dim>
inline void PointVector<Dim>::pconstruct(int i){}

template<const int Dim>
double PointVector<Dim>::get(int i) const{
	assert(i <= Dim);
	return comp[i];
}

template<const int Dim>
double PointVector<Dim>::getdx() const{
	assert(Dim >= 1);
    return comp[0];
}

template<const int Dim>
double PointVector<Dim>::getdy() const{
    assert(Dim >= 2);
    return comp[1];
}

template<const int Dim>
double PointVector<Dim>::getdz() const{
    assert(Dim >= 3);
    return comp[2];
}

template<const int Dim>
double PointVector<Dim>::getMagnitude() const{
	double mag = 0;
	for(int i = 0; i < Dim; i++){
		mag += comp[i] * comp[i];
	}
	return sqrt(mag);
}

template<const int Dim>
double PointVector<Dim>::sum_comp() const{
	double sum = 0;
	for(auto x : comp){
		sum += x;
	}
	return sum;
}

template<const int Dim>
void PointVector<Dim>::set(int i, double d){
	assert(i <= Dim);
	comp[i] = d;
}

template<const int Dim>
void PointVector<Dim>::setdx(double d){
	assert(Dim >= 1);
	comp[0] = d;
}

template<const int Dim>
void PointVector<Dim>::setdy(double d){
	assert(Dim >= 2);
	comp[1] = d;
}

template<const int Dim>
void PointVector<Dim>::setdz(double d){
	assert(Dim >= 3);
	comp[2] = d;
}

template<const int Dim>
PointVector<Dim>& PointVector<Dim>::add(PointVector<Dim> p){
	for(int i = 0; i < Dim; i++){
		comp[i] += p.comp[i];
	}
	return *this;
}

template<const int Dim>
PointVector<Dim>& PointVector<Dim>::sub(PointVector<Dim> p){
	for(int i = 0; i < Dim; i++){
		comp[i] -= p.comp[i];
	}
	return *this;
}

template<const int Dim>
PointVector<Dim> PointVector<Dim>::add(PointVector<Dim> p, PointVector<Dim> q){
	return p.add(q);
}

template<const int Dim>
PointVector<Dim> PointVector<Dim>::sub(PointVector<Dim> p, PointVector<Dim> q){
	return p.sub(q);
}

template<const int Dim>
PointVector<Dim>& PointVector<Dim>::mul_comp(PointVector<Dim> p){
	for(int i = 0; i < Dim; i++){
		comp[i] *= p.comp[i];
	}
	return *this;
}

template<const int Dim>
PointVector<Dim>& PointVector<Dim>::mul_cross(PointVector<Dim> p){
	return *this;
}

template<>
inline PointVector<3>& PointVector<3>::mul_cross(PointVector<3> p){
	double x = comp[1] * p.comp[2] - comp[2] * p.comp[1];
	double y = comp[2] * p.comp[0] - comp[0] * p.comp[2];
	comp[2] = comp[0] * p.comp[1] - comp[1] * p.comp[0];
	comp[0] = x;
	comp[1] = y;
	return *this;
}

template<>
inline PointVector<7>& PointVector<7>::mul_cross(PointVector<7> p){
	comp[0] = comp[1] * p.comp[3] - comp[3] * p.comp[1] + comp[2] * p.comp[6] - comp[6] * p.comp[2] + comp[4] * p.comp[5] - comp[5] * p.comp[4];
	comp[1] = comp[2] * p.comp[4] - comp[4] * p.comp[2] + comp[3] * p.comp[0] - comp[0] * p.comp[3] + comp[5] * p.comp[6] - comp[6] * p.comp[5];
	comp[2] = comp[3] * p.comp[5] - comp[5] * p.comp[3] + comp[4] * p.comp[1] - comp[1] * p.comp[4] + comp[6] * p.comp[0] - comp[0] * p.comp[6];
	comp[3] = comp[4] * p.comp[6] - comp[6] * p.comp[4] + comp[5] * p.comp[2] - comp[2] * p.comp[5] + comp[0] * p.comp[1] - comp[1] * p.comp[0];
	comp[4] = comp[5] * p.comp[0] - comp[0] * p.comp[5] + comp[6] * p.comp[3] - comp[3] * p.comp[6] + comp[1] * p.comp[2] - comp[2] * p.comp[1];
	comp[5] = comp[6] * p.comp[1] - comp[1] * p.comp[6] + comp[0] * p.comp[4] - comp[4] * p.comp[0] + comp[2] * p.comp[3] - comp[3] * p.comp[2];
	comp[6] = comp[0] * p.comp[2] - comp[2] * p.comp[0] + comp[1] * p.comp[5] - comp[5] * p.comp[1] + comp[3] * p.comp[4] - comp[4] * p.comp[3];
	return *this;
}

template<const int Dim>
PointVector<Dim>& PointVector<Dim>::mul(long double d){
	for(int i = 0; i < Dim; i++){
		comp[i] *= d;
	}
	return *this;
}

template<const int Dim>
double PointVector<Dim>::mul_dot(PointVector<Dim> p, PointVector<Dim> q){
	double result = 0;
	for(int i = 0; i < Dim; i++){
		result += p.comp[i] * q.comp[i];
	}
	return result;
}

template<const int Dim>
PointVector<Dim> PointVector<Dim>::mul_comp(PointVector<Dim> p, PointVector<Dim> q){
	return p.mul_comp(q);
}

template<const int Dim>
PointVector<Dim> PointVector<Dim>::mul_cross(PointVector<Dim> p, PointVector<Dim> q){
	return p.mul_cross(q);
}

template<const int Dim>
PointVector<Dim> PointVector<Dim>::mul(double d, PointVector<Dim> p){
	return p.mul(d);
}

template<const int Dim>
PointVector<Dim>& PointVector<Dim>::div_comp(PointVector<Dim> p){
    for(int i = 0; i < Dim; i++){
		comp[i] /= p.comp[i];
	}
	return *this;
}

template<const int Dim>
PointVector<Dim>& PointVector<Dim>::div(double d){
	for(int i = 0; i < Dim; i++){
		comp[i] /= d;
	}
	return *this;
}

template<const int Dim>
PointVector<Dim> PointVector<Dim>::div_comp(PointVector<Dim> p, PointVector<Dim> q){
	return p.div_comp(q);
}

template<const int Dim>
PointVector<Dim> PointVector<Dim>::div(double d, PointVector p){
	return p.div(d);
}

template<const int Dim>
PointVector<Dim>& PointVector<Dim>::pow(double d){
	for(int i = 0; i < Dim; i++){
		comp[i] = pow(comp[i], d);
	}
	return *this;
}

template<const int Dim>
PointVector<Dim>& PointVector<Dim>::pow_comp(PointVector p){
	for(int i = 0; i < Dim; i++){
		comp[i] = pow(comp[i], p.comp[i]);
	}
}

template<const int Dim>
PointVector<Dim> PointVector<Dim>::pow(double d, PointVector p){
	return p.pow(d);
}

template<const int Dim>
PointVector<Dim> PointVector<Dim>::pow_comp(PointVector p, PointVector q){
	return p.pow_comp(q);
}

template<const int Dim>
PointVector<Dim>& PointVector<Dim>::set_min_comp(PointVector<Dim> p){
	for(int i = 0; i < Dim; i++){
		*(comp+i) = *(comp+i) < *(p.comp+i) ? *(comp+i) : *(p.comp+i);
	}
	return *this;
}

template<const int Dim>
PointVector<Dim>& PointVector<Dim>::set_max_comp(PointVector<Dim> p){
	for(int i = 0; i < Dim; i++){
		*(comp+i) = *(comp+i) > *(p.comp+i) ? *(comp+i) : *(p.comp+i);
	}
	return *this;
}

template<const int Dim>
PointVector<Dim> PointVector<Dim>::min_comp(PointVector p, PointVector q){
	return p.set_min_comp(q);
}

template<const int Dim>
PointVector<Dim> PointVector<Dim>::max_comp(PointVector p, PointVector q){
	return p.set_max_comp(q);
}

template<const int Dim>
bool PointVector<Dim>::is_min_comp(PointVector<Dim> p) const{
	for(int i = 0; i < Dim; i++){
		if(comp[i] > p.comp[i])
			return false;
	}
	return true;
}

template<const int Dim>
bool PointVector<Dim>::is_max_comp(PointVector<Dim> p) const{
	for(int i = 0; i < Dim; i++){
		if(comp[i] < p.comp[i])
			return false;
	}
	return true;
}

template<const int Dim>
bool PointVector<Dim>::is_eq_comp(PointVector<Dim> p) const{
	for(int i = 0; i < Dim; i++){
		if(comp[i] != p.comp[i])
			return false;
	}
	return true;
}

template<const int Dim>
PointVector<Dim>& PointVector<Dim>::make_unit(){
	double mag = getMagnitude();
	for(int i = 0; i < Dim; i++){
		comp[i] /= mag; 
	}
	return *this;
}

template<const int Dim>
PointVector<Dim> PointVector<Dim>::make_unit(PointVector<Dim> p){
	return p.make_unit();
}

template<const int Dim>
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

template<const int Dim>
PointVector<Dim> PointVector<Dim>::project(PointVector p, PointVector q){
	return p.project(q);
}

template<const int Dim>
double PointVector<Dim>::taxicab_distance(PointVector p, PointVector q){
	double res;
	for(int i = 0; i < Dim; i++){
		res += abs(p.comp[i] - q.comp[i]);
	}
	return res;
}

template<const int Dim>
std::array<bool, Dim> PointVector<Dim>::operator ==(PointVector<Dim> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] == p.comp[i];
	}
	return result;
}

template<const int Dim>
std::array<bool, Dim> PointVector<Dim>::operator !=(PointVector<Dim> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] != p.comp[i];
	}
	return result;
}

template<const int Dim>
std::array<bool, Dim> PointVector<Dim>::operator >(PointVector<Dim> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] > p.comp[i];
	}
	return result;
}

template<const int Dim>
std::array<bool, Dim> PointVector<Dim>::operator <(PointVector<Dim> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] < p.comp[i];
	}
	return result;
}

template<const int Dim>
std::array<bool, Dim> PointVector<Dim>::operator >=(PointVector<Dim> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] >= p.comp[i];
	}
	return result;
}

template<const int Dim>
std::array<bool, Dim> PointVector<Dim>::operator <=(PointVector<Dim> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] <= p.comp[i];
	}
	return result;
}

template<const int Dim>
bool Boolarr::all(std::array<bool,Dim> a){
	for(int i = 0; i < Dim; i++){
		if(!a[i]){
			return false;
		}
	}
	return true;
}

template<const int Dim>
bool Boolarr::any(std::array<bool,Dim> a){
	for(int i = 0; i < Dim; i++){
		if(a[i]){
			return true;
		}
	}
	return false;
}

template<const int Dim>
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
