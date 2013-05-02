/* 
 * File:   NURBS.h
 * Author: elias
 *
 * Created on April 24, 2013, 4:42 PM
 */

#ifndef NURBSSEV_H
#define	NURBSSEV_H

#include "PointVector.h"

double def_param_axis_func(double t, double u);

class NURBSSEV {    //Non Uniform Rational B-Spline Surface Encapsulated Volume
public:
    NURBSSEV(double (*x)(double, double) = def_param_axis_func, double (*y)(double, double) = def_param_axis_func, double (*z)(double, double) = def_param_axis_func);
    NURBSSEV(const NURBSSEV& orig);
    virtual ~NURBSSEV();
    
    NURBSSEV Unite(NURBSSEV a);
    NURBSSEV Intersect(NURBSSEV a);
    NURBSSEV Complement(NURBSSEV a);
    NURBSSEV Differatiate(NURBSSEV a);
    
    NURBSSEV& operator=(NURBSSEV v) const;
	
    bool is_equal_to(const NURBSSEV& v);
	bool is_subset_of(const NURBSSEV& v);
	bool is_superset_of(const NURBSSEV& v);
	bool isIntersecting(const NURBSSEV& v);
	
	double distance_between(const NURBSSEV& v);
	
	double getVolume();
    double getSurfaceArea();
	
private:
    void calculate_mesh();
	void use_hq_mesh();
    
private:
    double (*mesh_vertecies)[3];
	double (*hq_mesh)[3];
	
	bool param_func_valid;
	double (*pfucs[3])(double, double);
};

#endif	/* NURBSSEV_H */

