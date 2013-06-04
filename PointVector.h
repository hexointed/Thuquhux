/* 
 * File:   PointVector.h
 * Author: Elias Forsberg
 *
 * Created on December 26, 2012, 4:19 PM
 */

#ifndef POINTVECTOR_H
#define	POINTVECTOR_H

#include <array>

template<unsigned int Dim = 3>
class PointVector{
    
public:
	PointVector();
	PointVector(double composants[Dim]);
	
	template<unsigned int D2>
	PointVector(PointVector<D2> orig);
	
	template<typename... Tail>
	PointVector(Tail... t);

private:
	template<typename First, typename... Tail>
	inline void pconstruct(int i, First f, Tail... t);
	inline void pconstruct(int i);
    
private:
	double comp[Dim];
    
public:
	double get(int i) const;
	double getdx() const;
	double getdy() const;
	double getdz() const;
	
	double getMagnitude() const;
	double sum_comp() const;
	
	void set(int i, double d);
	void setdx(double d);
	void setdy(double d);
	void setdz(double d);
    
	PointVector& add(PointVector p);
	PointVector& sub(PointVector p);
	static PointVector add(PointVector p, PointVector q);
	static PointVector sub(PointVector p, PointVector q);
	
	PointVector& mul_comp(PointVector p);
	PointVector& mul_cross(PointVector p);
	PointVector& mul(long double d);
	static double mul_dot(PointVector p, PointVector q);
	static PointVector mul_comp(PointVector p, PointVector q);
	static PointVector mul_cross(PointVector p, PointVector q);
	static PointVector mul(double d, PointVector p);
	
	PointVector& div_comp(PointVector p);
	PointVector& div(double d);
	static PointVector div_comp(PointVector p, PointVector q);
	static PointVector div(double d, PointVector p);
	
	PointVector& pow(double d);
	PointVector& pow_comp(PointVector p);
	static PointVector pow(double d, PointVector p);
	static PointVector pow_comp(PointVector p, PointVector q);
	
	PointVector& set_min_comp(PointVector p);
	PointVector& set_max_comp(PointVector p);
	static PointVector min_comp(PointVector p, PointVector q);
	static PointVector max_comp(PointVector p, PointVector q);
	
	bool is_min_comp(PointVector p) const;
	bool is_max_comp(PointVector p) const;
	bool is_eq_comp (PointVector p) const;
	
	PointVector& make_unit();
	static PointVector make_unit(PointVector p);
	
	PointVector& project(PointVector p);
	static PointVector project(PointVector p, PointVector q);
	static double taxicab_distance(PointVector p, PointVector q);
	
	std::array<bool, Dim> operator==	(PointVector p) const;
	std::array<bool, Dim> operator!=	(PointVector p) const;
	std::array<bool, Dim> operator>	(PointVector p) const;
	std::array<bool, Dim> operator<	(PointVector p) const;
	std::array<bool, Dim> operator>=	(PointVector p) const;
	std::array<bool, Dim> operator<=	(PointVector p) const;
};

namespace Boolarr{
	template<unsigned int Dim>
	bool all(std::array<bool, Dim> a);
	template<unsigned int Dim>
	bool any(std::array<bool, Dim> a);
	template<unsigned int Dim>
	bool most(std::array<bool, Dim> a);
}

#endif	/* POINTVECTOR_H */

#include "PointVector.cpp"