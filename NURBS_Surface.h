/* 
 * File:   NURBS.h
 * Author: elias
 *
 * Created on April 24, 2013, 4:42 PM
 */

#ifndef NURBS_H
#define	NURBS_H

class NURBS_Surface {
public:
    NURBS_Surface();
    NURBS_Surface(const NURBS_Surface& orig);
    virtual ~NURBS_Surface();
    
    NURBS_Surface Unite(NURBS_Surface a);
    NURBS_Surface Intersect(NURBS_Surface a);
    NURBS_Surface Complement(NURBS_Surface a);
    NURBS_Surface Differatiate(NURBS_Surface a);
    
    NURBS_Surface& operator=(NURBS_Surface v) const;
    
    bool operator==(const NURBS_Surface& v) const;
    bool operator!=(const NURBS_Surface& v) const;
    bool operator< (const NURBS_Surface& v) const;
    bool operator> (const NURBS_Surface& v) const;
    bool operator<=(const NURBS_Surface& v) const;
    bool operator>=(const NURBS_Surface& v) const;
    
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

#endif	/* NURBS_H */

