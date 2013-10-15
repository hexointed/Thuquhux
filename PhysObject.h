/* 
 * File:   PhysObject.h
 * Author: Charles Gilljam
 *
 * Created on April 28, 2013, 6:59 PM
 */

#ifndef PHYSOBJECT_H
#define	PHYSOBJECT_H

#include "PointVector.h"
#include "Material.h"
#include "Geometry/Parametric_Surface.h"

class PhysObject {
public:
    PhysObject();
    PhysObject(const PhysObject& orig);
    virtual ~PhysObject();
    
    void unite(PhysObject a);
    void intersect(PhysObject a);
    void complement(PhysObject a);
    void differentiate(PhysObject);
    
    bool isInObject(PointVector<> a);
	
	double& density();
	Material& material();
	double& volume();
	PointVector<>& position();
	PointVector<>& velocity();
	Parametric_Surface& surface();
	
	void calcVolume();

	static void collision(PhysObject&,PhysObject&);
    
private:
	Material material;
	double volume;
	PointVector<> position;
	PointVector<> velocity;
	Parametric_Surface surface;
	PointVector<> rotation;
	
	
};

#endif	/* PHYSOBJECT_H */

