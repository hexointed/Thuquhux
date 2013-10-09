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

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>::PointVector():
	comp {}
{}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>::PointVector(double composants[Dim]){
	std::copy(composants, composants+Dim, comp);
}

template<int Dim, typename Numeric>
template<int D2>
PointVector<Dim, Numeric>::PointVector(PointVector<D2> orig):
	comp {}
{
	constexpr int m = std::min(Dim, D2);
	std::copy(orig.comp, orig.comp + m, comp);
}

template<int Dim, typename Numeric>
template<typename... Tail>
PointVector<Dim, Numeric>::PointVector(Tail... t){
	PointVector();
	pconstruct(0, t...);
}

template<int Dim, typename Numeric>
template<typename First, typename... Tail>
inline void PointVector<Dim, Numeric>::pconstruct(int i, First f, Tail... t){
	comp[i] = f;
	pconstruct(i+1, t...);
}

template<int Dim, typename Numeric>
inline void PointVector<Dim, Numeric>::pconstruct(int /*i*/){}

template<int Dim, typename Numeric>
double PointVector<Dim, Numeric>::get(int i) const{
	assert(i <= Dim);
	return comp[i];
}

template<int Dim, typename Numeric>
double PointVector<Dim, Numeric>::getdx() const{
	static_assert(Dim >= 1, "This PointVector does not have an x-component");
    return comp[0];
}

template<int Dim, typename Numeric>
double PointVector<Dim, Numeric>::getdy() const{
    static_assert(Dim >= 2, "This PointVector does not have a y-component");
    return comp[1];
}

template<int Dim, typename Numeric>
double PointVector<Dim, Numeric>::getdz() const{
    static_assert(Dim >= 3, "This PointVector does not have a z-component");
    return comp[2];
}

template<int Dim, typename Numeric>
double PointVector<Dim, Numeric>::getMagnitude() const{
	double mag = 0;
	for(int i = 0; i < Dim; i++){
		mag += comp[i] * comp[i];
	}
	return sqrt(mag);
}

template<int Dim, typename Numeric>
double PointVector<Dim, Numeric>::sum_comp() const{
	double sum = 0;
	for(auto x : comp){
		sum += x;
	}
	return sum;
}

template<int Dim, typename Numeric>
void PointVector<Dim, Numeric>::set(int i, double d){
	assert(i <= Dim);
	comp[i] = d;
}

template<int Dim, typename Numeric>
void PointVector<Dim, Numeric>::setdx(double d){
	static_assert(Dim >= 1, "This PointVector does not have an x-component");
	comp[0] = d;
}

template<int Dim, typename Numeric>
void PointVector<Dim, Numeric>::setdy(double d){
	static_assert(Dim >= 2, "This PointVector does not have a y-component");
	comp[1] = d;
}

template<int Dim, typename Numeric>
void PointVector<Dim, Numeric>::setdz(double d){
	static_assert(Dim >= 3, "This PointVector does not have a z-component");
	comp[2] = d;
}

template<int Dim, typename Numeric>
inline PointVector<Dim, Numeric> PointVector<Dim, Numeric>::operator +(const PointVector<Dim, Numeric> r) const{
	return PointVector<Dim, Numeric>::add(*this, r);
}

template<int Dim, typename Numeric>
inline PointVector<Dim, Numeric> PointVector<Dim, Numeric>::operator -(const PointVector<Dim, Numeric> r) const{
	return PointVector<Dim, Numeric>::sub(*this, r);
}

template<int Dim, typename Numeric>
inline PointVector<Dim, Numeric> PointVector<Dim, Numeric>::operator -() const{
	return PointVector<Dim, Numeric>::mul(-1, *this);
}

template<int Dim, typename Numeric>
inline PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::operator +=(const PointVector<Dim, Numeric> r){
	this->add(r);
	return *this;
}

template<int Dim, typename Numeric>
inline PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::operator -=(const PointVector<Dim, Numeric> r){
	this->sub(r);
	return *this;
}

template<int Dim, typename Numeric>
inline PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::operator *=(const double r){
	this->mul(r);
	return *this;
}

template<int Dim, typename Numeric>
inline PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::operator /=(const double r){
	this->div(r);
	return *this;
}

template<int D, typename Numeric>
inline PointVector<D, Numeric> operator*(const PointVector<D> l, const double r){
	return PointVector<D>::mul(r, l);
}

template<int D, typename Numeric>
inline PointVector<D, Numeric> operator*(const double l, const PointVector<D> r){
	return PointVector<D>::mul(l, r);
}

template<int D, typename Numeric>
inline PointVector<D, Numeric> operator/(const PointVector<D> l, const double r){
	return PointVector<D>::div(r, l);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::add(PointVector<Dim, Numeric> p){
	for(int i = 0; i < Dim; i++){
		comp[i] += p.comp[i];
	}
	return *this;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::sub(PointVector<Dim, Numeric> p){
	for(int i = 0; i < Dim; i++){
		comp[i] -= p.comp[i];
	}
	return *this;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::add(PointVector<Dim, Numeric> p, PointVector<Dim, Numeric> q){
	return p.add(q);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::sub(PointVector<Dim, Numeric> p, PointVector<Dim, Numeric> q){
	return p.sub(q);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::mul_comp(PointVector<Dim, Numeric> p){
	for(int i = 0; i < Dim; i++){
		comp[i] *= p.comp[i];
	}
	return *this;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::mul_cross(PointVector<Dim, Numeric> p){
	return *this;
}
/*
template<>
template<typename Numeric>
inline PointVector<3, Numeric>& PointVector<3, Numeric>::mul_cross(PointVector<3, Numeric> p){
	PointVector<3, Numeric> q(*this);
	comp[0] = q.comp[1] * p.comp[2] - q.comp[2] * p.comp[1];
	comp[1] = q.comp[2] * p.comp[0] - q.comp[0] * p.comp[2];
	comp[2] = q.comp[0] * p.comp[1] - q.comp[1] * p.comp[0];
	return *this;
}

template<typename Numeric>
inline PointVector<7, Numeric>& PointVector<7, Numeric>::mul_cross(PointVector<7, Numeric> p){
	PointVector<7, Numeric> q(*this);
	comp[0] = q.comp[1] * p.comp[3] - q.comp[3] * p.comp[1] + q.comp[2] * p.comp[6] - q.comp[6] * p.comp[2] + q.comp[4] * p.comp[5] - q.comp[5] * p.comp[4];
	comp[1] = q.comp[2] * p.comp[4] - q.comp[4] * p.comp[2] + q.comp[3] * p.comp[0] - q.comp[0] * p.comp[3] + q.comp[5] * p.comp[6] - q.comp[6] * p.comp[5];
	comp[2] = q.comp[3] * p.comp[5] - q.comp[5] * p.comp[3] + q.comp[4] * p.comp[1] - q.comp[1] * p.comp[4] + q.comp[6] * p.comp[0] - q.comp[0] * p.comp[6];
	comp[3] = q.comp[4] * p.comp[6] - q.comp[6] * p.comp[4] + q.comp[5] * p.comp[2] - q.comp[2] * p.comp[5] + q.comp[0] * p.comp[1] - q.comp[1] * p.comp[0];
	comp[4] = q.comp[5] * p.comp[0] - q.comp[0] * p.comp[5] + q.comp[6] * p.comp[3] - q.comp[3] * p.comp[6] + q.comp[1] * p.comp[2] - q.comp[2] * p.comp[1];
	comp[5] = q.comp[6] * p.comp[1] - q.comp[1] * p.comp[6] + q.comp[0] * p.comp[4] - q.comp[4] * p.comp[0] + q.comp[2] * p.comp[3] - q.comp[3] * p.comp[2];
	comp[6] = q.comp[0] * p.comp[2] - q.comp[2] * p.comp[0] + q.comp[1] * p.comp[5] - q.comp[5] * p.comp[1] + q.comp[3] * p.comp[4] - q.comp[4] * p.comp[3];
	return *this;
}*/

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::mul(long double d){
	for(int i = 0; i < Dim; i++){
		comp[i] *= d;
	}
	return *this;
}

template<int Dim, typename Numeric>
double PointVector<Dim, Numeric>::mul_dot(PointVector<Dim, Numeric> p, PointVector<Dim, Numeric> q){
	double result = 0;
	for(int i = 0; i < Dim; i++){
		result += p.comp[i] * q.comp[i];
	}
	return result;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::mul_comp(PointVector<Dim, Numeric> p, PointVector<Dim, Numeric> q){
	return p.mul_comp(q);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::mul_cross(PointVector<Dim, Numeric> p, PointVector<Dim, Numeric> q){
	return p.mul_cross(q);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::mul(double d, PointVector<Dim, Numeric> p){
	return p.mul(d);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::div_comp(PointVector<Dim, Numeric> p){
    for(int i = 0; i < Dim; i++){
		comp[i] /= p.comp[i];
	}
	return *this;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::div(double d){
	for(int i = 0; i < Dim; i++){
		comp[i] /= d;
	}
	return *this;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::div_comp(PointVector<Dim, Numeric> p, PointVector<Dim, Numeric> q){
	return p.div_comp(q);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::div(double d, PointVector p){
	return p.div(d);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::pow(double d){
	for(int i = 0; i < Dim; i++){
		comp[i] = pow(comp[i], d);
	}
	return *this;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::pow_comp(PointVector p){
	for(int i = 0; i < Dim; i++){
		comp[i] = pow(comp[i], p.comp[i]);
	}
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::pow(double d, PointVector p){
	return p.pow(d);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::pow_comp(PointVector p, PointVector q){
	return p.pow_comp(q);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::set_min_comp(PointVector<Dim, Numeric> p){
	for(int i = 0; i < Dim; i++){
		*(comp+i) = *(comp+i) < *(p.comp+i) ? *(comp+i) : *(p.comp+i);
	}
	return *this;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::set_max_comp(PointVector<Dim, Numeric> p){
	for(int i = 0; i < Dim; i++){
		*(comp+i) = *(comp+i) > *(p.comp+i) ? *(comp+i) : *(p.comp+i);
	}
	return *this;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::min_comp(PointVector p, PointVector q){
	return p.set_min_comp(q);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::max_comp(PointVector p, PointVector q){
	return p.set_max_comp(q);
}

template<int Dim, typename Numeric>
bool PointVector<Dim, Numeric>::is_min_comp(PointVector<Dim, Numeric> p) const{
	for(int i = 0; i < Dim; i++){
		if(comp[i] > p.comp[i])
			return false;
	}
	return true;
}

template<int Dim, typename Numeric>
bool PointVector<Dim, Numeric>::is_max_comp(PointVector<Dim, Numeric> p) const{
	for(int i = 0; i < Dim; i++){
		if(comp[i] < p.comp[i])
			return false;
	}
	return true;
}

template<int Dim, typename Numeric>
bool PointVector<Dim, Numeric>::is_eq_comp(PointVector<Dim, Numeric> p) const{
	for(int i = 0; i < Dim; i++){
		if(comp[i] != p.comp[i])
			return false;
	}
	return true;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::make_unit(){
	double mag = getMagnitude();
	for(int i = 0; i < Dim; i++){
		comp[i] /= mag; 
	}
	return *this;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::make_unit(PointVector<Dim, Numeric> p){
	return p.make_unit();
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::project(PointVector p){
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

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::project(PointVector p, PointVector q){
	return p.project(q);
}

template<int Dim, typename Numeric>
double PointVector<Dim, Numeric>::taxicab_distance(PointVector p, PointVector q){
	double res;
	for(int i = 0; i < Dim; i++){
		res += abs(p.comp[i] - q.comp[i]);
	}
	return res;
}

template<int Dim, typename Numeric>
std::array<bool, Dim> PointVector<Dim, Numeric>::operator ==(PointVector<Dim, Numeric> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] == p.comp[i];
	}
	return result;
}

template<int Dim, typename Numeric>
std::array<bool, Dim> PointVector<Dim, Numeric>::operator !=(PointVector<Dim, Numeric> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] != p.comp[i];
	}
	return result;
}

template<int Dim, typename Numeric>
std::array<bool, Dim> PointVector<Dim, Numeric>::operator >(PointVector<Dim, Numeric> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] > p.comp[i];
	}
	return result;
}

template<int Dim, typename Numeric>
std::array<bool, Dim> PointVector<Dim, Numeric>::operator <(PointVector<Dim, Numeric> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] < p.comp[i];
	}
	return result;
}

template<int Dim, typename Numeric>
std::array<bool, Dim> PointVector<Dim, Numeric>::operator >=(PointVector<Dim, Numeric> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] >= p.comp[i];
	}
	return result;
}

template<int Dim, typename Numeric>
std::array<bool, Dim> PointVector<Dim, Numeric>::operator <=(PointVector<Dim, Numeric> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] <= p.comp[i];
	}
	return result;
}

template<int Dim, typename Numeric>
bool Boolarr::all(std::array<bool,Dim> a){
	for(int i = 0; i < Dim; i++){
		if(!a[i]){
			return false;
		}
	}
	return true;
}

template<int Dim, typename Numeric>
bool Boolarr::any(std::array<bool,Dim> a){
	for(int i = 0; i < Dim; i++){
		if(a[i]){
			return true;
		}
	}
	return false;
}

template<int Dim, typename Numeric>
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
