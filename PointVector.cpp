/* 
 * File:   PointVector.cpp
 * Author: Elias Forsberg
 *
 * Created on December 26, 2012, 4:20 PM
 */

#include "PointVector.h"
#include <math.h>

PointVector::PointVector(){
	this->dx = 0;
	this->dy = 0;
	this->dz = 0;
}

PointVector::PointVector(double x, double y, double z){
    this->dx = x;
    this->dy = y;
    this->dz = z;
}

double PointVector::getdx(){
    return this->dx;
}

double PointVector::getdy(){
    return this->dy;
}

double PointVector::getdz(){
    return this->dz;
}

double PointVector::getMagnitude(){
	return sqrt(dx*dx + dy*dy + dz*dz);
}

double PointVector::setdx(double d){
	this->dx = d;
}

double PointVector::setdy(double d){
	this->dy = d;
}

double PointVector::setdz(double d){
	this->dz = d;
}

PointVector* PointVector::add(PointVector& p){
	this->dx += p.getdx();
	this->dy += p.getdy();
	this->dz += p.getdz();
	return this;
}

PointVector* PointVector::sub(PointVector& p){
    this->dx -= p.getdx();
	this->dy -= p.getdy();
	this->dz -= p.getdz();
	return this;
}

PointVector* PointVector::mul_comp(PointVector& p){
    this->dx *= p.getdx();
	this->dy *= p.getdy();
	this->dz *= p.getdz();
	return this;
}

PointVector* PointVector::mul_cross(PointVector& p){
	this->dx = this->dy * p.getdz() - this->dz * p.getdy();
	this->dy = this->dz * p.getdx() - this->dx * p.getdz();
	this->dz = this->dx * p.getdy() - this->dy * p.getdx();
	return this;
}

PointVector* PointVector::mul(long double d){
	this->dx *= d;
	this->dy *= d;
	this->dz *= d;
	return this;
}

double PointVector::mul_dot(PointVector& p, PointVector& q){
	return q.getdx() * p.getdx() + q.getdy() * p.getdy() + q.getdz() * p.getdz();
}

PointVector* PointVector::div_comp(PointVector& p){
    this->dx /= p.getdx();
	this->dy /= p.getdy();
	this->dz /= p.getdz();
	return this;
}

PointVector* PointVector::div(double d){
	this->dx /= d;
	this->dy /= d;
	this->dz /= d;
	return this;
}

PointVector* PointVector::set_min_comp(PointVector& p){
	for(int i = 0; i < 3; i++){
		*((&this->dx)+i) = *((&this->dx)+i) < *((&p.dx)+i) ? *((&this->dx)+i) : *((&p.dx)+i);
	}
	return this;
}

PointVector* PointVector::set_max_comp(PointVector& p){
	for(int i = 0; i < 3; i++){
		*((&this->dx)+i) = *((&this->dx)+i) > *((&p.dx)+i) ? *((&this->dx)+i) : *((&p.dx)+i);
	}
	return this;
}

bool PointVector::is_min_comp(PointVector& p){
	return this->dx > p.dx && this->dy > p.dy && this->dz > p.dz;
}

bool PointVector::is_max_comp(PointVector& p){
	return this->dx < p.dx && this->dy < p.dy && this->dz < p.dz;
}