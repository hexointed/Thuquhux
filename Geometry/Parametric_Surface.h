/* 
 * File:   Parametric_Surface.h
 * Author: Elias Forsberg
 *
 * Created on April 24, 2013, 4:42 PM
 *
 * Parametric_Surface is used to represent complex 3-dimensional shapes using a
 * Triangle_Mesh. It also supports a few higher level operations as volume 
 * calculation and constructive solid geometry.
 */

#ifndef PARAMETRIC_SURFACE_H
#define	PARAMETRIC_SURFACE_H

#include "PointVector.h"
#include "Triangle.h"
#include "Triangle_Mesh.h"

#include <vector>
#include <functional>

namespace Geometry{

	PointVector<> def_param_axis_func(PointVector<2> params);

	class Parametric_Surface {
	public:
		Parametric_Surface() = default;
		Parametric_Surface(const Parametric_Surface&);
		Parametric_Surface(PointVector<> pos);
		template<typename Functor>
		Parametric_Surface(Functor f, PointVector<> pos);
		virtual ~Parametric_Surface();
		
		static Parametric_Surface unite(Parametric_Surface a, Parametric_Surface b);
		static Parametric_Surface intersect(Parametric_Surface a, Parametric_Surface b);
		static Parametric_Surface differatiate(Parametric_Surface a, Parametric_Surface b);
		
		void Unite(Parametric_Surface a);
		void Intersect(Parametric_Surface a);
		void Complement(Parametric_Surface a);
		void Differatiate(Parametric_Surface a);
		
		Parametric_Surface& operator=(const Parametric_Surface& orig) = default;
		
		bool is_equal_to(const Parametric_Surface& v);
		bool is_subset_of(const Parametric_Surface& v);
		bool is_superset_of(const Parametric_Surface& v);
		bool isIntersecting(Parametric_Surface& v);
		
		std::pair<PointVector<>,PointVector<>> collision_data(Parametric_Surface& v);
		
		double distance_between(const Parametric_Surface& v);
		bool pointIsWithin(PointVector<> p);
		bool lineIsWithin(PointVector<> p);
		
		double getVolume();
		double getSurfaceArea();
		
		void rotate(PointVector<> axis, double angle);
		void drawMesh();
		template<typename Functor>
		void calculate_mesh(Functor pfunc);
		
	private:
		Geometry::Triangle_Mesh mesh;
		
		int mesh_detail;
		int mesh_length;
		
		bool prop_updated;
		double volume;
		
	public:
		PointVector<> bound_box[2];
		PointVector<> position;
	
	private:
		void slice_and_erase(Parametric_Surface a, 
		                     std::function<bool(Triangle,Parametric_Surface,Parametric_Surface)> f);
	};
		
}
#endif	/* PARAMETRIC_SURFACE_H */

#include "Parametric_Surface.hpp"
