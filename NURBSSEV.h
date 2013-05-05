/* 
 * File:   NURBS.h
 * Author: elias
 *
 * Created on April 24, 2013, 4:42 PM
 */

#ifndef NURBSSEV_H
#define	NURBSSEV_H

#include "PointVector.h"

double def_param_axis_func_x(double t, double u);
double def_param_axis_func_y(double t, double u);
double def_param_axis_func_z(double t, double u);

class NURBSSEV {    //Non Uniform Rational B-Spline Surface Encapsulated Volume
public:
    NURBSSEV(double (*x)(double, double) = def_param_axis_func_x, double (*y)(double, double) = def_param_axis_func_y, double (*z)(double, double) = def_param_axis_func_z);
    NURBSSEV(const NURBSSEV& orig);
    virtual ~NURBSSEV();
    
    NURBSSEV Unite(NURBSSEV a, PointVector pos);
    NURBSSEV Intersect(NURBSSEV a, PointVector pos);
    NURBSSEV Complement(NURBSSEV a, PointVector pos);
    NURBSSEV Differatiate(NURBSSEV a, PointVector pos);
    
    NURBSSEV& operator=(NURBSSEV v) const;
	
    bool is_equal_to(const NURBSSEV& v);
	bool is_subset_of(const NURBSSEV& v);
	bool is_superset_of(const NURBSSEV& v);
	bool isIntersecting(const NURBSSEV& v);
	
	double distance_between(const NURBSSEV& v);
	bool pointIsWithin(PointVector p);
	bool lineIsWithin(PointVector p);
	
	double getVolume();
    double getSurfaceArea();
	
	void drawMesh();
	void calculate_mesh();
	void use_hq_mesh();
    
private:
    double (*mesh_vertecies)[3];
	double (*hq_mesh)[3];
	
	int mesh_detail;
	int hq_mesh_detail;
	
	bool param_func_valid;
	double (*pfuncs[3])(double, double);
	
	bool prop_updated;
	double volume;
	
public:
	PointVector * bound_box[2];
	PointVector * position;
};

#endif	/* NURBSSEV_H */

