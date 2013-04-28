/* 
 * File:   NURBS.h
 * Author: elias
 *
 * Created on April 24, 2013, 4:42 PM
 */

#ifndef NURBSSEV_H
#define	NURBSSEV_H

class NURBSSEV {    //Non Uniform Rational B-Spline Surface Encapsulated Volume
public:
    NURBSSEV();
    NURBSSEV(const NURBSSEV& orig);
    virtual ~NURBSSEV();
    
    NURBSSEV Unite(NURBSSEV a);
    NURBSSEV Intersect(NURBSSEV a);
    NURBSSEV Complement(NURBSSEV a);
    NURBSSEV Differatiate(NURBSSEV a);
    
    NURBSSEV& operator=(NURBSSEV v) const;
    
    bool operator&&(const NURBSSEV& v) const;   //Intersection check
    bool operator==(const NURBSSEV& v) const;
    bool operator!=(const NURBSSEV& v) const;
    bool operator< (const NURBSSEV& v) const;   //Subset of
    bool operator> (const NURBSSEV& v) const;   //Superset of
    bool operator<=(const NURBSSEV& v) const;
    bool operator>=(const NURBSSEV& v) const;
    
private:
    void re_calculate_mesh();
    
public:
    double (*mesh_vertecies)[3];
    
private:
    double * knots;
    double (*ctrlpoints)[3];
    double * weights;
    int ctrlpts_width;
    int ctrlpts_depth;
};

#endif	/* NURBSSEV_H */

