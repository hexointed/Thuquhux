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
	PointVector(const PointVector& orig);
    
private:
    double dx, dy, dz;
    
public:
    double getdx();
    double getdy();
    double getdz();
    
    PointVector* add(PointVector& p);
    PointVector* sub(PointVector& p);
	static PointVector* add(PointVector& p, PointVector& q);
	static PointVector* sub(PointVector& p, PointVector& q);
	
	PointVector* mul_comp(PointVector& p);
	PointVector* mul_cross(PointVector& p);
    PointVector* mul(long double d);
	static double mul_dot(PointVector& p, PointVector& q);
	static PointVector* mul_comp(PointVector& p, PointVector& q);
	static PointVector* mul_cross(PointVector& p, PointVector& q);
    static PointVector* mul(long double d, PointVector& p);
	
    PointVector* div_comp(PointVector& p);
    PointVector* div(double d);
	static PointVector* div_comp(PointVector& p, PointVector& q);
    static PointVector* div(double d, PointVector& p);
};

#endif	/* POINTVECTOR_H */