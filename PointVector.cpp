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

PointVector* PointVector::add(PointVector *p){
    return new PointVector(this->dx + p->getdx(), this->dy + p->getdy(), this->dz + p->getdz());
}

PointVector* PointVector::sub(PointVector *p){
    return new PointVector(this->dx - p->getdx(), this->dy - p->getdy(), this->dz - p->getdz());
}

PointVector* PointVector::mul(PointVector *p){
    return new PointVector(this->dx * p->getdx(), this->dy * p->getdy(), this->dz * p->getdz());
}

double PointVector::mul_dot(PointVector* p){
	return this->dx * p->getdx() + this->dy * p->getdy() + this->dz * p->getdz();
}

PointVector* PointVector::mul_cross(PointVector* p){
	return new PointVector(this->dy * p->getdz() - this->dz * p->getdy(), this->dz * p->getdx() - this->dx * p->getdz(), this->dx * p->getdy() - this->dy * p->dx);
}

PointVector* PointVector::mul(long double d){
    return new PointVector(this->dx * d, this->dy * d, this->dz * d);
}

PointVector* PointVector::div(PointVector *p){
    return new PointVector(this->dx / p->getdx(), this->dy / p->getdy(), this->dz / p->getdz());
}