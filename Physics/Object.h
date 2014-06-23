/* 
 * File:   Object.h
 * Author: Charles Gilljam / Elias Forsberg
 *
 * Created on April 28, 2013, 6:59 PM
 */

#ifndef PHYSICS_OBJECT_H
#define	PHYSICS_OBJECT_H

#include "../Geometry/PointVector.h"
#include "Material.h"
#include "../Geometry/Parametric_Surface.h"
#include "PhysHandler.h"

using Geometry::Parametric_Surface;

namespace Physics {

	class Object : public Parametric_Surface {
	public:
	
		static PhysHandler default_handler;

		static void create(bool addToList = 1, Parametric_Surface surface = Parametric_Surface(Geometry::def_param_axis_func, {0,0,0}), PhysHandler& handler = default_handler, PointVector<> velocity = {0,0,0});
		static Object& create_return(bool addToList = 1, Parametric_Surface surface = Parametric_Surface(Geometry::def_param_axis_func, {0,0,0}), PhysHandler& handler = default_handler, PointVector<> velocity = {0,0,0});	

		Object(const Object& orig) = default;
		virtual ~Object() = default;
	    
		void unite(Object a);
		void intersect(Object a);
		void complement(Object a);
		void differentiate(Object);
	    
		bool isInObject(PointVector<> a);
	
		double& density();
		Material& material();
		double& volume();
		PointVector<>& previous_position();
		PointVector<>& velocity();
		std::pair<PointVector<>, double>& rotation();

		PointVector<>& acceleration();

		std::vector<std::pair<PointVector<> , double>>& impulses();
	
		void calcVolume();
		void accelerate(PointVector<> a);
		void addImpulse(PointVector<> a, double time);
	
	
		static void collision(Object& obj1,Object& obj2, PointVector<> collide_at, PointVector<> normal);
	    
	private:
		Object(Parametric_Surface surface = Parametric_Surface(Geometry::def_param_axis_func, {0,0,0}), PointVector<> velocity = {0,0,0});

		PointVector<> _previous_position;
		Material _material;
		double _volume;
		PointVector<> _velocity;
		PointVector<> _acceleration;
		std::vector<std::pair<PointVector<> , double>> _impulses;
		std::pair<PointVector<>, double> _rotation;

	public:
	
	
	};
}

#endif	/* PHYSICS_OBJECT_H */

