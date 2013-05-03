/* 
 * File:   PointVector.cpp
 * Author: Elias Forsberg
 *
 * Created on December 26, 2012, 4:20 PM
 */

#include "PointVector.h"

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