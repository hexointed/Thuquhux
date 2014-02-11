/* 
 * File:   PhysObject.h
 * Author: Charles Gilljam
 *
 * Created on April 28, 2013, 6:59 PM
 */

#ifndef PHYSOBJECT_H
#define	PHYSOBJECT_H

#include "../Geometry/Geometry.h"
#include "Material.h"
#include "../Geometry/Parametric_Surface.h"
#include "PhysHandler.h"

using Geometry::Parametric_Surface;

class PhysObject {
public:
	
	static PhysHandler default_handler;

	static void create(bool addToList = 1, Parametric_Surface surface = Parametric_Surface(Geometry::def_param_axis_func, {0,0,0}), PhysHandler& handler = default_handler, Geometry::Vector<> velocity = {0,0,0});
	static PhysObject& create_return(bool addToList = 1, Parametric_Surface surface = Parametric_Surface(Geometry::def_param_axis_func, {0,0,0}), PhysHandler& handler = default_handler, Geometry::Vector<> velocity = {0,0,0});	

	PhysObject(const PhysObject& orig);
	virtual ~PhysObject();
    
	void unite(PhysObject a);
	void intersect(PhysObject a);
	void complement(PhysObject a);
	void differentiate(PhysObject);
    
	bool isInObject(Geometry::Vector<> a);
	
	double& density();
	Material& material();
	double& volume();
	Geometry::Vector<>& previous_position();
	Geometry::Vector<>& position();
	Geometry::Vector<>& velocity();
	std::pair<Geometry::Vector<>, double>& rotation();

	Geometry::Vector<>& acceleration();

	std::vector<std::pair<Geometry::Vector<> , double>>& impulses();

	Parametric_Surface& surface();
	
	void calcVolume();
	void accelerate(Geometry::Vector<> a);
	void addImpulse(Geometry::Vector<> a, double time);
	
	
	static void collision(PhysObject& obj1,PhysObject& obj2, Geometry::Vector<> collide_at, Geometry::Vector<> normal);
    
private:
	PhysObject(Parametric_Surface surface = Parametric_Surface(Geometry::def_param_axis_func, {0,0,0}), Geometry::Vector<> velocity = {0,0,0});

	Geometry::Vector<> _previous_position;
	Material _material;
	double _volume;
	Geometry::Vector<> _velocity;
	Geometry::Vector<> _acceleration;
	std::vector<std::pair<Geometry::Vector<> , double>> _impulses;
	Parametric_Surface _surface;
	std::pair<Geometry::Vector<>, double> _rotation;

public:
	
	
};

#endif	/* PHYSOBJECT_H */

