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
#include "../Geometry/Parametric_Surface.h"
#include "PhysHandler.h"

using Geometry::Parametric_Surface;

class PhysObject {
public:
	
	static PhysHandler default_handler;

	static void create(bool addToList = 1, Parametric_Surface surface = {Geometry::def_param_axis_func}, PhysHandler& handler = default_handler, PointVector<> velocity = {0,0,0});
	static PhysObject& create_return(bool addToList = 1, Parametric_Surface surface = {Geometry::def_param_axis_func}, PhysHandler& handler = default_handler, PointVector<> velocity = {0,0,0});	

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
	PointVector<>& previous_position();
	PointVector<>& position();
	PointVector<>& velocity();
	std::pair<PointVector<>, double> rotation();

	PointVector<>& acceleration();

	std::vector<std::pair<PointVector<> , double>>& impulses();

	Parametric_Surface& surface();
	
	void calcVolume();
	void accelerate(PointVector<> a);
	void addImpulse(PointVector<> a, double time);
	
	
	static void collision(PhysObject& obj1,PhysObject& obj2, PointVector<> collide_at, PointVector<> normal);
    
private:
	PhysObject(Parametric_Surface surface = {Geometry::def_param_axis_func}, PhysHandler handler = default_handler, PointVector<> velocity = {0,0,0});

	PointVector<> _previous_position;
	Material _material;
	double _volume;
	PointVector<> _velocity;
	PointVector<> _acceleration;
	std::vector<std::pair<PointVector<> , double>> _impulses;
	Parametric_Surface _surface;
	std::pair<PointVector<>, double> _rotation;

public:
	
	
};

#endif	/* PHYSOBJECT_H */

