/* 
 * File:   PointVector.cpp
 * Author: Elias Forsberg
 *
 * Created on December 26, 2012, 4:20 PM
 */

#include "PointVector.h"

PointVector::PointVector(long double x, long double y, long double z){
    this->dx = x;
    this->dy = y;
    this->dz = z;
}

long double PointVector::getdx(){
    return this->dx;
}

long double PointVector::getdy(){
    return this->dy;
}

long double PointVector::getdz(){
    return this->dz;
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

PointVector* PointVector::add(PointVector *p){
    return new PointVector(this->dx + p->getdx(), this->dy + p->getdy(), this->dz + p->getdz());
}

PointVector* PointVector::sub(PointVector *p){
    return new PointVector(this->dx - p->getdx(), this->dy - p->getdy(), this->dz - p->getdz());
}

PointVector* PointVector::mul(PointVector *p){
    return new PointVector(this->dx * p->getdx(), this->dy * p->getdy(), this->dz * p->getdz());
}

PointVector* PointVector::mul(long double d){
    return new PointVector(this->dx * d, this->dy * d, this->dz * d);
}

PointVector* PointVector::div(PointVector *p){
    return new PointVector(this->dx / p->getdx(), this->dy / p->getdy(), this->dz / p->getdz());
}