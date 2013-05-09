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
	
	double getMagnitude();
	
	double setdx(double d);
	double setdy(double d);
	double setdz(double d);
    
    PointVector* add(PointVector& p);
    PointVector* sub(PointVector& p);
	
	PointVector* mul_comp(PointVector& p);
	PointVector* mul_cross(PointVector& p);
    PointVector* mul(long double d);
	static double mul_dot(PointVector& p, PointVector& q);
	
    PointVector* div_comp(PointVector& p);
    PointVector* div(double d);
	
	PointVector* set_min_comp(PointVector& p);
	PointVector* set_max_comp(PointVector& p);
	bool is_min_comp(PointVector& p);
	bool is_max_comp(PointVector& p);
};

#endif	/* POINTVECTOR_H */
