/* 
 * File:   PointVector.h
 * Author: Elias Forsberg
 *
 * Created on December 26, 2012, 4:19 PM
 */

#ifndef POINTVECTOR_H
#define	POINTVECTOR_H

#include <array>

template<const int Dim = 3>
class PointVector{
    
public:
	PointVector();
	PointVector(double composants[Dim]);
    PointVector(double x, double y, double z);
	PointVector(const PointVector& orig);
    
private:
    double comp[Dim];
    
public:
	double get(int i);
    double getdx();
    double getdy();
    double getdz();
	
	double getMagnitude();
	
	void set(int i, double d);
	void setdx(double d);
	void setdy(double d);
	void setdz(double d);
    
    PointVector* add(PointVector& p);
    PointVector* sub(PointVector& p);
	
	PointVector* mul_comp(PointVector& p);
	PointVector* mul_cross(PointVector& p);
    PointVector* mul(long double d);
	static double mul_dot(PointVector& p, PointVector& q);
	
    PointVector* div_comp(PointVector& p);
    PointVector* div(double d);
	
	PointVector* pow(double d);
	PointVector* pow_comp(PointVector& p);
	
	PointVector* set_min_comp(PointVector& p);
	PointVector* set_max_comp(PointVector& p);
	bool is_min_comp(PointVector& p);
	bool is_max_comp(PointVector& p);
	
	std::array<bool, Dim> operator==	(PointVector& p);
	std::array<bool, Dim> operator!=	(PointVector& p);
	std::array<bool, Dim> operator>	(PointVector& p);
	std::array<bool, Dim> operator<	(PointVector& p);
	std::array<bool, Dim> operator>=	(PointVector& p);
	std::array<bool, Dim> operator<=	(PointVector& p);
};

#endif	/* POINTVECTOR_H */
