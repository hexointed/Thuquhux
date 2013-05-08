/* 
 * File:   NURBS.h
 * Author: elias
 *
 * Created on April 24, 2013, 4:42 PM
 */

#ifndef PARAMETRIC_SURFACE_H
#define	PARAMETRIC_SURFACE_H

#include "PointVector.h"
#include <vector>

double def_param_axis_func_x(double t, double u);
double def_param_axis_func_y(double t, double u);
double def_param_axis_func_z(double t, double u);

class Parametric_Surface {    //Non Uniform Rational B-Spline Surface Encapsulated Volume
public:
    Parametric_Surface(double (*x)(double, double) = def_param_axis_func_x, double (*y)(double, double) = def_param_axis_func_y, double (*z)(double, double) = def_param_axis_func_z);
    Parametric_Surface(const Parametric_Surface& orig);
    virtual ~Parametric_Surface();
    
    friend Parametric_Surface Unite(Parametric_Surface a, Parametric_Surface b, PointVector pos);
    friend Parametric_Surface Intersect(Parametric_Surface a, Parametric_Surface b, PointVector pos);
    friend Parametric_Surface Complement(Parametric_Surface a, Parametric_Surface b, PointVector pos);
    friend Parametric_Surface Differatiate(Parametric_Surface a, Parametric_Surface b, PointVector pos);
	
	void Unite(Parametric_Surface a, PointVector pos);
    void Intersect(Parametric_Surface a, PointVector pos);
    void Complement(Parametric_Surface a, PointVector pos);
    void Differatiate(Parametric_Surface a, PointVector pos);
    
    Parametric_Surface& operator=(Parametric_Surface v) const;
	
    bool is_equal_to(const Parametric_Surface& v);
	bool is_subset_of(const Parametric_Surface& v);
	bool is_superset_of(const Parametric_Surface& v);
	bool isIntersecting(const Parametric_Surface& v);
	
	double distance_between(const Parametric_Surface& v);
	bool pointIsWithin(PointVector p);
	bool lineIsWithin(PointVector p);
	
	double getVolume();
    double getSurfaceArea();
	
	void drawMesh();
	void calculate_mesh();
	void use_hq_mesh();
    
private:
	std::vector<PointVector (*)> mesh_vertecies;
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

#endif	/* PARAMETRIC_SURFACE_H */

