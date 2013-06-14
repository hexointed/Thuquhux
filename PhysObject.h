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

class PhysObject {
public:
    PhysObject();
    PhysObject(const PhysObject& orig);
    virtual ~PhysObject();
    
    void Unite(PhysObject a);
    void Intersect(PhysObject a);
    void Complement(PhysObject a);
    void Differentiate(PhysObject);
    
    bool isInObject(PointVector<> a);
	
	Material material;
	double volume;
    
private:
	void setMass(double mass);
	
};

#endif	/* PHYSOBJECT_H */

