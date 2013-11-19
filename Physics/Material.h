/* 
 * File:   Material.h
 * Author: user
 *
 * Created on May 29, 2013, 1:32 PM
 */

#ifndef MATERIAL_H
#define	MATERIAL_H

struct Material {
    Material();
//    Material(const Material& orig);
	virtual ~Material();
	
    double inertialDens;
    double gravitationDens;
    int friction;
    int elasticity;
	
	void setDensity(double density);
    

};

#endif	/* MATERIAL_H */

