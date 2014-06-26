/*
 * File:   Geometry/Surface.h
 * Author: Elias Forsberg
 *
 * Created on April 24, 2013, 4:42 PM
 *
 * Surface is used to represent complex 3-dimensional shapes using a
 * Triangle_Mesh. It also supports a few higher level operations as volume
 * calculation and constructive solid geometry.
 */

#ifndef GEOMETRY_SURFACE_H
#define	GEOMETRY_SURFACE_H

#include "Geometry.h"
#include "Triangle_Mesh.h"

#include <vector>
#include <functional>

namespace Graphics{
	class DrawHandler;
}

namespace Geometry{

	Geometry::Vector<> def_param_axis_func(Geometry::Vector<2> params);

	class Surface {
		friend class ::Graphics::DrawHandler;
	public:
		Surface() = default;
		Surface(const Surface&);
		Surface(Geometry::Vector<> pos);
		template<typename Functor>
		Surface(Functor f, Geometry::Vector<> pos);
		virtual ~Surface();
		
		static Surface unite(Surface a, Surface b);
		static Surface intersect(Surface a, Surface b);
		static Surface differatiate(Surface a, Surface b);
		
		void Unite(Surface a);
		void Intersect(Surface a);
		void Complement(Surface a);
		void Differatiate(Surface a);
		
		Surface& operator=(const Surface& orig) = default;
		
		bool is_equal_to(const Surface& v);
		bool is_subset_of(const Surface& v);
		bool is_superset_of(const Surface& v);
		bool isIntersecting(Surface& v);
		
		std::pair<Geometry::Vector<>,Geometry::Vector<>> collision_data(Surface& v);
		
		double distance_between(const Surface& v);
		bool pointIsWithin(Geometry::Vector<> p);
		bool lineIsWithin(Geometry::Vector<> p);
		
		double getVolume();
		double getSurfaceArea();
		
		void rotate(Geometry::Vector<> axis, double angle);
		void drawMesh();
		
	private:
		template<typename Functor>
		class Finder;
		
		template<typename Functor>
		void calculate_mesh(Functor f);
		
		template<typename Functor>
		void calculate_2d(Functor f);
		template<typename Functor>
		void calculate_3d(Functor f);
		
	public: //This should change.
		Geometry::Triangle_Mesh mesh;
		
	private:
		int mesh_detail;
		int mesh_length;
		
		bool prop_updated;
		double volume;
		
	public:
		Geometry::Vector<> bound_box[2];
		Geometry::Vector<> position;
	
	private:
		void slice_and_erase(Surface a, 
		                     std::function<bool(Triangle,Surface,Surface)> f);
	};
		
}
#endif	/* GEOMETRY_SURFACE_H */

#include "Surface.hpp"
