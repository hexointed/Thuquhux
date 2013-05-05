/* 
 * File:   PhysObject.h
 * Author: elias
 *
 * Created on April 28, 2013, 6:59 PM
 */

#ifndef PHYSOBJECT_H
#define	PHYSOBJECT_H

class PhysObject {
public:
    PhysObject();
    PhysObject(const PhysObject& orig);
    virtual ~PhysObject();
    
    void Unite(PhysObject a);
    void Intersect(PhysObject a);
    void Complement(PhysObject a);
    void Differentiate(PhysObject);
    
    bool isInObject(PointVector a);
    
private:
};

#endif	/* PHYSOBJECT_H */

