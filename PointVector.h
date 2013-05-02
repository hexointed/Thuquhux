/* 
 * File:   PointVector.h
 * Author: Elias Forsberg
 *
 * Created on December 26, 2012, 4:19 PM
 */

#ifndef POINTVECTOR_H
#define	POINTVECTOR_H

class PointVector{
    
public:
    PointVector(double x, double y, double z);
    
private:
    double dx, dy, dz;
    
public:
    double getdx();
    double getdy();
    double getdz();
    
    PointVector* add(PointVector *p);
    PointVector* sub(PointVector *p);
    PointVector* mul(PointVector *p);
	double mul_dot(PointVector *p);
	PointVector* mul_cross(PointVector *p);
    PointVector* mul(long double d);
    PointVector* div(PointVector *p);
    
};

#endif	/* POINTVECTOR_H */