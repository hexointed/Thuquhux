/* 
 * File:   Parametric_Surface.h
 * Author: Elias Forsberg
 *
 * Created on April 24, 2013, 4:42 PM
 */

#ifndef PARAMETRIC_SURFACE_H
#define	PARAMETRIC_SURFACE_H

#include "PointVector.h"
#include "Geometry.h"
#include <vector>

namespace Geometry{

	PointVector<> def_param_axis_func(PointVector<2> params);

	class Parametric_Surface {
	public:
		template<typename Functor>
		Parametric_Surface(Functor f, PointVector<> pos = {0,0,0});
		virtual ~Parametric_Surface();
		
		friend Parametric_Surface Unite(Parametric_Surface a, Parametric_Surface b, PointVector<> pos);
		friend Parametric_Surface Intersect(Parametric_Surface a, Parametric_Surface b, PointVector<> pos);
		friend Parametric_Surface Complement(Parametric_Surface a, Parametric_Surface b, PointVector<> pos);
		friend Parametric_Surface Differatiate(Parametric_Surface a, Parametric_Surface b, PointVector<> pos);
		
		void Unite(Parametric_Surface a);
		void Intersect(Parametric_Surface a);
		void Complement(Parametric_Surface a);
		void Differatiate(Parametric_Surface a);
		
		Parametric_Surface& operator=(Parametric_Surface v) const;
		
		bool is_equal_to(const Parametric_Surface& v);
		bool is_subset_of(const Parametric_Surface& v);
		bool is_superset_of(const Parametric_Surface& v);
		bool isIntersecting(const Parametric_Surface& v);
		
		double distance_between(const Parametric_Surface& v);
		bool pointIsWithin(PointVector<> p);
		bool lineIsWithin(PointVector<> p);
		
		double getVolume();
		double getSurfaceArea();
		
		void drawMesh();
		template<typename Functor>
		void calculate_mesh(Functor pfunc);
		
	private:
		std::vector<Triangle> mesh_vertecies;
		
		int mesh_detail;
		const int mesh_length;
		
		bool prop_updated;
		double volume;
		
	public:
		PointVector<> bound_box[2];
		PointVector<> position;
	};
		
}
#endif	/* PARAMETRIC_SURFACE_H */

#include "Parametric_Surface.hpp"