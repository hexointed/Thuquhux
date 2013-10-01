/* 
 * File:   PointVector.h
 * Author: Elias Forsberg
 *
 * Created on December 26, 2012, 4:19 PM
 * 
 * This class is hoped to be useful for representing N-dimensional points and 
 * vectors. It includes several arithmetic operations that are common for vectors.
 */

#ifndef POINTVECTOR_H
#define	POINTVECTOR_H

#include <array>

template<int Dim = 3>
class PointVector{
    
public:
	PointVector();
	PointVector(double composants[Dim]);
	
	template<int D2>
	PointVector(PointVector<D2> orig);
	
	template<typename... Tail>
	PointVector(Tail... t);

private:
	/*
	 *  Constructor helper functions (for the variadic template constructor)
	 */
	template<typename First, typename... Tail>
	inline void pconstruct(int i, First f, Tail... t);
	inline void pconstruct(int i);
    
private:
	double comp[Dim];
    
public:
	/*
	 * Returns composants of the PointVector<Dim>. 
	 * x,y and z represent comp[0], comp[1] and comp[2], respectively. 
	 */
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
	
	/*
	 * Some common arithmetic operations. There exist several versions of many
	 * of these operations; as operators, member methods, and static methods.
	 */
	
	inline PointVector operator +(const PointVector r) const;
	inline PointVector operator -(const PointVector r) const;
	inline PointVector operator -() const;
	
	inline PointVector& operator+=(const PointVector r);
	inline PointVector& operator-=(const PointVector r);
	inline PointVector& operator*=(const double r);
	inline PointVector& operator/=(const double r);
	
	template<int D>
	friend PointVector<D> operator *(const PointVector<D> l, const double r);
	template<int D>
	friend PointVector<D> operator *(const double l, const PointVector<D> r);
	template<int D>
	friend PointVector<D> operator /(const PointVector<D> l, const double r);
	
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
	
	/*
	 * a is considered max_comp(b) if all components of a are equal or bigger
	 * than their respective component in b
	 */
	
	PointVector& set_min_comp(PointVector p);
	PointVector& set_max_comp(PointVector p);
	static PointVector min_comp(PointVector p, PointVector q);
	static PointVector max_comp(PointVector p, PointVector q);
	
	bool is_min_comp(PointVector p) const;
	bool is_max_comp(PointVector p) const;
	bool is_eq_comp (PointVector p) const;
	
	/*
	 * A unit vector is a vector with the magnitude 1. make_unit() and 
	 * make_unit(p) scale down their vectors so that their magnitude is one,
	 * but the relative sizes of the composants remain.
	 */
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
	template<int Dim>
	bool all(std::array<bool, Dim> a);
	template<int Dim>
	bool any(std::array<bool, Dim> a);
	template<int Dim>
	bool most(std::array<bool, Dim> a);
}

#endif	/* POINTVECTOR_H */

#include "PointVector.hpp"
