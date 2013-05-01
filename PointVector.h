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
    PointVector(long double x, long double y, long double z);
    
private:
    double dx, dy, dz;
    
public:
    long double getdx();
    long double getdy();
    long double getdz();
    
    PointVector* add(PointVector *p);
    PointVector* sub(PointVector *p);
    PointVector* mul(PointVector *p);
    PointVector* mul(long double d);
    PointVector* div(PointVector *p);
    
};

#endif	/* POINTVECTOR_H */