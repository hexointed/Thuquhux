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

template<int Dim>
PointVector<Dim>::PointVector():
	comp {}
{}

template<int Dim>
PointVector<Dim>::PointVector(double composants[Dim]){
	std::copy(composants, composants+Dim, comp);
}

template<int Dim>
template<int D2>
PointVector<Dim>::PointVector(PointVector<D2> orig):
	comp {}
{
	constexpr int m = std::min(Dim, D2);
	std::copy(orig.comp, orig.comp + m, comp);
}

template<int Dim>
template<typename... Tail>
PointVector<Dim>::PointVector(Tail... t){
	PointVector();
	pconstruct(0, t...);
}

template<int Dim>
template<typename First, typename... Tail>
inline void PointVector<Dim>::pconstruct(int i, First f, Tail... t){
	comp[i] = f;
	pconstruct(i+1, t...);
}

template<int Dim>
inline void PointVector<Dim>::pconstruct(int i){}

template<int Dim>
double PointVector<Dim>::get(int i) const{
	assert(i <= Dim);
	return comp[i];
}

template<int Dim>
double PointVector<Dim>::getdx() const{
	static_assert(Dim >= 1, "This PointVector does not have an x-component");
    return comp[0];
}

template<int Dim>
double PointVector<Dim>::getdy() const{
    static_assert(Dim >= 2, "This PointVector does not have a y-component");
    return comp[1];
}

template<int Dim>
double PointVector<Dim>::getdz() const{
    static_assert(Dim >= 3, "This PointVector does not have a z-component");
    return comp[2];
}

template<int Dim>
double PointVector<Dim>::getMagnitude() const{
	double mag = 0;
	for(int i = 0; i < Dim; i++){
		mag += comp[i] * comp[i];
	}
	return sqrt(mag);
}

template<int Dim>
double PointVector<Dim>::sum_comp() const{
	double sum = 0;
	for(auto x : comp){
		sum += x;
	}
	return sum;
}

template<int Dim>
void PointVector<Dim>::set(int i, double d){
	assert(i <= Dim);
	comp[i] = d;
}

template<int Dim>
void PointVector<Dim>::setdx(double d){
	static_assert(Dim >= 1, "This PointVector does not have an x-component");
	comp[0] = d;
}

template<int Dim>
void PointVector<Dim>::setdy(double d){
	static_assert(Dim >= 2, "This PointVector does not have a y-component");
	comp[1] = d;
}

template<int Dim>
void PointVector<Dim>::setdz(double d){
	static_assert(Dim >= 3, "This PointVector does not have a z-component");
	comp[2] = d;
}

template<int Dim>
inline PointVector<Dim> PointVector<Dim>::operator +(const PointVector<Dim> r) const{
	return PointVector<Dim>::add(*this, r);
}

template<int Dim>
inline PointVector<Dim> PointVector<Dim>::operator -(const PointVector<Dim> r) const{
	return PointVector<Dim>::sub(*this, r);
}

template<int Dim>
inline PointVector<Dim> PointVector<Dim>::operator -() const{
	return PointVector<Dim>::mul(-1, *this);
}

template<int Dim>
inline PointVector<Dim>& PointVector<Dim>::operator +=(const PointVector<Dim> r){
	this->add(r);
	return *this;
}

template<int Dim>
inline PointVector<Dim>& PointVector<Dim>::operator -=(const PointVector<Dim> r){
	this->sub(r);
	return *this;
}

template<int Dim>
inline PointVector<Dim>& PointVector<Dim>::operator *=(const double r){
	this->mul(r);
	return *this;
}

template<int Dim>
inline PointVector<Dim>& PointVector<Dim>::operator /=(const double r){
	this->div(r);
	return *this;
}

template<int D>
inline PointVector<D> operator*(const PointVector<D> l, const double r){
	return PointVector<D>::mul(r, l);
}

template<int D>
inline PointVector<D> operator*(const double l, const PointVector<D> r){
	return PointVector<D>::mul(l, r);
}

template<int D>
inline PointVector<D> operator/(const PointVector<D> l, const double r){
	return PointVector<D>::div(r, l);
}

template<int Dim>
PointVector<Dim>& PointVector<Dim>::add(PointVector<Dim> p){
	for(int i = 0; i < Dim; i++){
		comp[i] += p.comp[i];
	}
	return *this;
}

template<int Dim>
PointVector<Dim>& PointVector<Dim>::sub(PointVector<Dim> p){
	for(int i = 0; i < Dim; i++){
		comp[i] -= p.comp[i];
	}
	return *this;
}

template<int Dim>
PointVector<Dim> PointVector<Dim>::add(PointVector<Dim> p, PointVector<Dim> q){
	return p.add(q);
}

template<int Dim>
PointVector<Dim> PointVector<Dim>::sub(PointVector<Dim> p, PointVector<Dim> q){
	return p.sub(q);
}

template<int Dim>
PointVector<Dim>& PointVector<Dim>::mul_comp(PointVector<Dim> p){
	for(int i = 0; i < Dim; i++){
		comp[i] *= p.comp[i];
	}
	return *this;
}

template<int Dim>
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

template<int Dim>
PointVector<Dim>& PointVector<Dim>::mul(long double d){
	for(int i = 0; i < Dim; i++){
		comp[i] *= d;
	}
	return *this;
}

template<int Dim>
double PointVector<Dim>::mul_dot(PointVector<Dim> p, PointVector<Dim> q){
	double result = 0;
	for(int i = 0; i < Dim; i++){
		result += p.comp[i] * q.comp[i];
	}
	return result;
}

template<int Dim>
PointVector<Dim> PointVector<Dim>::mul_comp(PointVector<Dim> p, PointVector<Dim> q){
	return p.mul_comp(q);
}

template<int Dim>
PointVector<Dim> PointVector<Dim>::mul_cross(PointVector<Dim> p, PointVector<Dim> q){
	return p.mul_cross(q);
}

template<int Dim>
PointVector<Dim> PointVector<Dim>::mul(double d, PointVector<Dim> p){
	return p.mul(d);
}

template<int Dim>
PointVector<Dim>& PointVector<Dim>::div_comp(PointVector<Dim> p){
    for(int i = 0; i < Dim; i++){
		comp[i] /= p.comp[i];
	}
	return *this;
}

template<int Dim>
PointVector<Dim>& PointVector<Dim>::div(double d){
	for(int i = 0; i < Dim; i++){
		comp[i] /= d;
	}
	return *this;
}

template<int Dim>
PointVector<Dim> PointVector<Dim>::div_comp(PointVector<Dim> p, PointVector<Dim> q){
	return p.div_comp(q);
}

template<int Dim>
PointVector<Dim> PointVector<Dim>::div(double d, PointVector p){
	return p.div(d);
}

template<int Dim>
PointVector<Dim>& PointVector<Dim>::pow(double d){
	for(int i = 0; i < Dim; i++){
		comp[i] = pow(comp[i], d);
	}
	return *this;
}

template<int Dim>
PointVector<Dim>& PointVector<Dim>::pow_comp(PointVector p){
	for(int i = 0; i < Dim; i++){
		comp[i] = pow(comp[i], p.comp[i]);
	}
}

template<int Dim>
PointVector<Dim> PointVector<Dim>::pow(double d, PointVector p){
	return p.pow(d);
}

template<int Dim>
PointVector<Dim> PointVector<Dim>::pow_comp(PointVector p, PointVector q){
	return p.pow_comp(q);
}

template<int Dim>
PointVector<Dim>& PointVector<Dim>::set_min_comp(PointVector<Dim> p){
	for(int i = 0; i < Dim; i++){
		*(comp+i) = *(comp+i) < *(p.comp+i) ? *(comp+i) : *(p.comp+i);
	}
	return *this;
}

template<int Dim>
PointVector<Dim>& PointVector<Dim>::set_max_comp(PointVector<Dim> p){
	for(int i = 0; i < Dim; i++){
		*(comp+i) = *(comp+i) > *(p.comp+i) ? *(comp+i) : *(p.comp+i);
	}
	return *this;
}

template<int Dim>
PointVector<Dim> PointVector<Dim>::min_comp(PointVector p, PointVector q){
	return p.set_min_comp(q);
}

template<int Dim>
PointVector<Dim> PointVector<Dim>::max_comp(PointVector p, PointVector q){
	return p.set_max_comp(q);
}

template<int Dim>
bool PointVector<Dim>::is_min_comp(PointVector<Dim> p) const{
	for(int i = 0; i < Dim; i++){
		if(comp[i] > p.comp[i])
			return false;
	}
	return true;
}

template<int Dim>
bool PointVector<Dim>::is_max_comp(PointVector<Dim> p) const{
	for(int i = 0; i < Dim; i++){
		if(comp[i] < p.comp[i])
			return false;
	}
	return true;
}

template<int Dim>
bool PointVector<Dim>::is_eq_comp(PointVector<Dim> p) const{
	for(int i = 0; i < Dim; i++){
		if(comp[i] != p.comp[i])
			return false;
	}
	return true;
}

template<int Dim>
PointVector<Dim>& PointVector<Dim>::make_unit(){
	double mag = getMagnitude();
	for(int i = 0; i < Dim; i++){
		comp[i] /= mag; 
	}
	return *this;
}

template<int Dim>
PointVector<Dim> PointVector<Dim>::make_unit(PointVector<Dim> p){
	return p.make_unit();
}

template<int Dim>
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

template<int Dim>
PointVector<Dim> PointVector<Dim>::project(PointVector p, PointVector q){
	return p.project(q);
}

template<int Dim>
double PointVector<Dim>::taxicab_distance(PointVector p, PointVector q){
	double res;
	for(int i = 0; i < Dim; i++){
		res += abs(p.comp[i] - q.comp[i]);
	}
	return res;
}

template<int Dim>
std::array<bool, Dim> PointVector<Dim>::operator ==(PointVector<Dim> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] == p.comp[i];
	}
	return result;
}

template<int Dim>
std::array<bool, Dim> PointVector<Dim>::operator !=(PointVector<Dim> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] != p.comp[i];
	}
	return result;
}

template<int Dim>
std::array<bool, Dim> PointVector<Dim>::operator >(PointVector<Dim> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] > p.comp[i];
	}
	return result;
}

template<int Dim>
std::array<bool, Dim> PointVector<Dim>::operator <(PointVector<Dim> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] < p.comp[i];
	}
	return result;
}

template<int Dim>
std::array<bool, Dim> PointVector<Dim>::operator >=(PointVector<Dim> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] >= p.comp[i];
	}
	return result;
}

template<int Dim>
std::array<bool, Dim> PointVector<Dim>::operator <=(PointVector<Dim> p) const{
	std::array<bool, Dim> result;
	for(int i = 0; i < Dim; i++){
		result[i] = comp[i] <= p.comp[i];
	}
	return result;
}

template<int Dim>
bool Boolarr::all(std::array<bool,Dim> a){
	for(int i = 0; i < Dim; i++){
		if(!a[i]){
			return false;
		}
	}
	return true;
}

template<int Dim>
bool Boolarr::any(std::array<bool,Dim> a){
	for(int i = 0; i < Dim; i++){
		if(a[i]){
			return true;
		}
	}
	return false;
}

template<int Dim>
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