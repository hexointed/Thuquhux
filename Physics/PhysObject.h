/* 
 * File:   PhysObject.h
 * Author: Charles Gilljam
 *
 * Created on April 28, 2013, 6:59 PM
 */

#ifndef PHYSOBJECT_H
#define	PHYSOBJECT_H

#include "../Geometry/PointVector.h"
#include "Material.h"
//#include "Geometry/Parametric_Surface.h"

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
	PointVector<>& acceleration();

	std::vector<std::pair<PointVector<> , double>>& impulses();

	//Parametric_Surface& surface();
	
	void calcVolume();
	void accelerate(PointVector<> a);
	void addImpulse(Pointvector a, double time)	
	
	
	static void collision(PhysObject&,PhysObject&);
    
private:
	Material _material;
	double _volume;
	PointVector<> _position;
	PointVector<> _velocity;
	PointVector<> _acceleration;

	std::vector<std::pair<PointVector<> , double>> _impulses;

	//Parametric_Surface _surface;
	PointVector<> _rotation;
	
	
};

#endif	/* PHYSOBJECT_H */

