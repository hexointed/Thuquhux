/* 
 * File:   PointVector.hpp
 * Author: Elias Forsberg
 *
 * Created on December 26, 2012, 4:20 PM
 */

#ifndef POINTVECTOR_CPP
#define POINTVECTOR_CPP

#include "PointVector.h"
#include <math.h>
#include <cassert>
#include <stdexcept>

template<int Dim, typename Numeric>
Numeric PointVector<Dim, Numeric>::get(int i) const{
	assert(i <= Dim);
	return comp[i];
}

template<int Dim, typename Numeric>
Numeric PointVector<Dim, Numeric>::magnitude() const{
	Numeric mag = 0;
	for(int i = 0; i < Dim; i++){
		mag += comp[i] * comp[i];
	}
	return sqrt(mag);
}

template<int Dim, typename Numeric>
Numeric PointVector<Dim, Numeric>::sum_comp() const{
	Numeric sum = 0;
	for(auto x : comp){
		sum += x;
	}
	return sum;
}

template<int Dim, typename Numeric>
Numeric& PointVector<Dim, Numeric>::operator[](int i) {
	return comp[i];
}

template<int Dim, typename Numeric>
Numeric PointVector<Dim, Numeric>::operator[](int i) const{
	return comp[i];
}

template<int Dim, typename Numeric>
void PointVector<Dim, Numeric>::set(int i, Numeric d){
	assert(i <= Dim);
	comp[i] = d;
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
	*this = *this + r;
	return *this;
}

template<int Dim, typename Numeric>
inline PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::operator -=(const PointVector<Dim, Numeric> r){
	*this = *this - r;
	return *this;
}

template<int Dim, typename Numeric>
inline PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::operator *=(const Numeric r){
	*this = *this * r;
	return *this;
}

template<int Dim, typename Numeric>
inline PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::operator /=(const Numeric r){
	*this = *this / r;
	return *this;
}

template<int D, typename Num>
inline PointVector<D, Num> operator*(const PointVector<D, Num> l, const Num r){
	return PointVector<D, Num>::mul(r, l);
}

template<int D, typename Num>
inline PointVector<D, Num> operator*(const Num l, const PointVector<D, Num> r){
	return PointVector<D, Num>::mul(l, r);
}

template<int D, typename Num>
inline PointVector<D, Num> operator/(const PointVector<D, Num> l, const Num r){
	return PointVector<D, Num>::div(r, l);
}

template<int D, typename Num>
inline PointVector<D, Num> operator/(const Num l, const PointVector<D, Num> r){
	PointVector<D, Num> a;
	for(int i = 0; i < D; i++){
		a.comp[i] = 1.0/r.comp [i];
	}
	return PointVector<D, Num>::mul_comp(a, l);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::add(PointVector<Dim, Numeric> p) const {
	PointVector tmp{};
	for(int i = 0; i < Dim; i++){
		tmp[i] = comp[i] + p.comp[i];
	}
	return tmp;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::sub(PointVector<Dim, Numeric> p) const {
	PointVector tmp{};
	for(int i = 0; i < Dim; i++){
		tmp[i] = comp[i] - p.comp[i];
	}
	return tmp;
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
Numeric PointVector<Dim, Numeric>::mul_dot(PointVector<Dim, Numeric> p) const {
	return p.mul_comp(*this).sum_comp();
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::mul_comp(PointVector<Dim, Numeric> p) const {
	PointVector tmp{};	
	for(int i = 0; i < Dim; i++){
		tmp[i] = comp[i] * p.comp[i];
	}
	return tmp;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::mul_cross(PointVector<Dim, Numeric> p) const {
	return Cross_product(*this, p);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::mul(Numeric d) const {
	PointVector tmp{};	
	for(int i = 0; i < Dim; i++){
		tmp[i] = comp[i] * d;
	}
	return tmp;
}

template<int Dim, typename Numeric>
Numeric PointVector<Dim, Numeric>::mul_dot(PointVector<Dim, Numeric> p, PointVector<Dim, Numeric> q){
	return p.mul_comp(q).sum_comp();
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::mul_comp(PointVector<Dim, Numeric> p, PointVector<Dim, Numeric> q){
	return p.mul_comp(q);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::mul_cross(PointVector<Dim, Numeric> p, PointVector<Dim, Numeric> q){
	return Cross_product(p,q);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::mul(Numeric d, PointVector<Dim, Numeric> p){
	return p.mul(d);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::div_comp(PointVector<Dim, Numeric> p) const {
	PointVector tmp{};	
	for(int i = 0; i < Dim; i++){
		tmp = comp[i] / p.comp[i];
	}
	return tmp;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::div(Numeric d) const {
	PointVector tmp{};	
	for(int i = 0; i < Dim; i++){
		tmp = comp[i] / d;
	}
	return tmp;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::div_comp(PointVector<Dim, Numeric> p, PointVector<Dim, Numeric> q){
	return p.div_comp(q);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::div(Numeric d, PointVector p){
	return p.div(d);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::pow(Numeric d) const {
	PointVector tmp{};
	for(int i = 0; i < Dim; i++){
		tmp[i] = pow(comp[i], d);
	}
	return tmp;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::pow_comp(PointVector p) const {
	PointVector tmp{};
	for(int i = 0; i < Dim; i++){
		tmp[i] = pow(comp[i], p.comp[i]);
	}
	return tmp;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::pow(Numeric d, PointVector p) {
	return p.pow(d);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::pow_comp(PointVector p, PointVector q){
	return p.pow_comp(q);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::set_min_comp(PointVector<Dim, Numeric> p){
	PointVector tmp{};
	for(int i = 0; i < Dim; i++){
		tmp[i] = comp[i] < p.comp[i] ? comp[i] : p.comp[i];
	}
	return tmp;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>& PointVector<Dim, Numeric>::set_max_comp(PointVector<Dim, Numeric> p){
	PointVector tmp{};
	for(int i = 0; i < Dim; i++){
		tmp[i] = comp[i] < p.comp[i] ? comp[i] : p.comp[i];
	}
	return tmp;
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
bool PointVector<Dim, Numeric>::is_min_comp(PointVector<Dim, Numeric> p) const {
	for(int i = 0; i < Dim; i++){
		if(comp[i] > p.comp[i])
			return false;
	}
	return true;
}

template<int Dim, typename Numeric>
bool PointVector<Dim, Numeric>::is_max_comp(PointVector<Dim, Numeric> p) const {
	for(int i = 0; i < Dim; i++){
		if(comp[i] < p.comp[i])
			return false;
	}
	return true;
}

template<int Dim, typename Numeric>
bool PointVector<Dim, Numeric>::is_eq_comp(PointVector<Dim, Numeric> p) const {
	for(int i = 0; i < Dim; i++){
		if(comp[i] != p.comp[i])
			return false;
	}
	return true;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::normalize() const {
	PointVector tmp{};
	for(int i = 0; i < Dim; i++){
		tmp[i] = comp[i] / magnitude(); 
	}
	return tmp;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::normalize(PointVector<Dim, Numeric> p){
	return p.make_unit();
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::reflect(PointVector<Dim, Numeric> normal) const {
	PointVector<Dim, Numeric> p = *this;
	normal.make_unit();
	auto tmp = 2.0 * mul_dot(p, normal) * normal - p;
	return tmp;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::project(PointVector p) const {
	PointVector<Dim, Numeric>& res = *this;
	mul_dot(res, p)/mul_dot(p,p) * p;
	return res;
}

template<int Dim, typename Numeric>
Numeric PointVector<Dim, Numeric>::taxicab_distance(PointVector p) const {
	PointVector res = *this - p;
	res.op_comp([] (Numeric n) {
		return n < 0 ? n : -n;
	});
	return res.sum_comp();
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::reflect(PointVector<Dim, Numeric> p, PointVector<Dim, Numeric> normal){
	return p.reflect(normal);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::project(PointVector p, PointVector q) {
	return p.project(q);
}

template<int Dim, typename Numeric>
Numeric PointVector<Dim, Numeric>::taxicab_distance(PointVector p, PointVector q){
	return p.taxicab_distance(q);
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::rotate(Numeric angle, PointVector<Dim, Numeric> axis) const {
	static_assert(Dim == 3, "rotate only implemented for 3D vectors.");
	axis.make_unit();
	const PointVector<3, Numeric> r1{cos(angle) + axis.getdx()*axis.getdx()*(1 - cos(angle)),
	                  axis.getdx()*axis.getdy()*(1 - cos(angle)) - axis.getdz()*sin(angle),
	                  axis.getdx()*axis.getdz()*(1 - cos(angle)) + axis.getdy()*sin(angle)};
	const PointVector<3, Numeric> r2{axis.getdy()*axis.getdx()*(1 - cos(angle)) + axis.getdz()*sin(angle),
	                  cos(angle) + axis.getdy()*axis.getdy()*(1 - cos(angle)),
	                  axis.getdy()*axis.getdz()*(1 - cos(angle)) - axis.getdx()*sin(angle)};
	const PointVector<3, Numeric> r3{axis.getdz()*axis.getdx()*(1 - cos(angle)) - axis.getdy()*sin(angle),
	                  axis.getdz()*axis.getdy()*(1 - cos(angle)) + axis.getdx()*sin(angle),
	                  cos(angle) + axis.getdz()*axis.getdz()*(1 - cos(angle))};
	*this = {PointVector<3, Numeric>::mul_dot(r1, *this),
	         PointVector<3, Numeric>::mul_dot(r2, *this),
	         PointVector<3, Numeric>::mul_dot(r3, *this)};
	return *this;
}

template<int Dim, typename Numeric>
template<typename Functor>
	PointVector<Dim, Numeric> PointVector<Dim, Numeric>::op_comp(Functor f) const {
	PointVector tmp = *this;
	for(Numeric& n : tmp){
		n = f(n);
	}
	return tmp;
}

template<int Dim, typename Numeric>
template<typename Functor>
PointVector<Dim, Numeric> PointVector<Dim, Numeric>::op_comp(PointVector<Dim, Numeric> p, Functor f) const {
	PointVector tmp = *this;
	for(int i = 0; i < Dim; i++){
		tmp[i] = f(comp[i], p.comp[i]);
	}
	return tmp;
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
PointVector<Dim, Numeric>::Cross_product::Cross_product(PointVector<Dim, Numeric> t, PointVector<Dim, Numeric> u){
	q = t;
	p = u;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>::Cross_product::operator PointVector<3, Numeric> () const{
	PointVector<3, Numeric> res;
	res.comp[0] = q.comp[1] * p.comp[2] - q.comp[2] * p.comp[1];
	res.comp[1] = q.comp[2] * p.comp[0] - q.comp[0] * p.comp[2];
	res.comp[2] = q.comp[0] * p.comp[1] - q.comp[1] * p.comp[0];
	return res;
}

template<int Dim, typename Numeric>
PointVector<Dim, Numeric>::Cross_product::operator PointVector<7, Numeric> () const{
	PointVector<7, Numeric> res;
	res.comp[0] = q.comp[1] * p.comp[3] - q.comp[3] * p.comp[1] + q.comp[2] * p.comp[6] - q.comp[6] * p.comp[2] + q.comp[4] * p.comp[5] - q.comp[5] * p.comp[4];
	res.comp[1] = q.comp[2] * p.comp[4] - q.comp[4] * p.comp[2] + q.comp[3] * p.comp[0] - q.comp[0] * p.comp[3] + q.comp[5] * p.comp[6] - q.comp[6] * p.comp[5];
	res.comp[2] = q.comp[3] * p.comp[5] - q.comp[5] * p.comp[3] + q.comp[4] * p.comp[1] - q.comp[1] * p.comp[4] + q.comp[6] * p.comp[0] - q.comp[0] * p.comp[6];
	res.comp[3] = q.comp[4] * p.comp[6] - q.comp[6] * p.comp[4] + q.comp[5] * p.comp[2] - q.comp[2] * p.comp[5] + q.comp[0] * p.comp[1] - q.comp[1] * p.comp[0];
	res.comp[4] = q.comp[5] * p.comp[0] - q.comp[0] * p.comp[5] + q.comp[6] * p.comp[3] - q.comp[3] * p.comp[6] + q.comp[1] * p.comp[2] - q.comp[2] * p.comp[1];
	res.comp[5] = q.comp[6] * p.comp[1] - q.comp[1] * p.comp[6] + q.comp[0] * p.comp[4] - q.comp[4] * p.comp[0] + q.comp[2] * p.comp[3] - q.comp[3] * p.comp[2];
	res.comp[6] = q.comp[0] * p.comp[2] - q.comp[2] * p.comp[0] + q.comp[1] * p.comp[5] - q.comp[5] * p.comp[1] + q.comp[3] * p.comp[4] - q.comp[4] * p.comp[3];
	return res;
}

template<int Dim, typename Numeric>
std::ostream& operator<<(std::ostream& out, PointVector<Dim, Numeric> d) {
	out << "{";
	for(int i = 0; i < Dim; i++){
		out << d.comp[i];
		if(i < Dim - 1){
			out << ", ";
		}
	}
	out << "}";
	return out;
}

	#endif /*POINTVECTOR_CPP*/
