/*
 * File:    Matrix.h
 * Author:  Elias Forsberg
 *
 * Created on December 23, 2014, 21:19
 *
 * The following class is hopefully going to be useful for representing 
 * matricies.
 */
 
#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include "Geometry.h"

namespace Geometry {

	template<int M, int N, typename Numeric = double>
	class Matrix {
	public:
		Matrix();
		explicit Matrix(Numeric composants[]);
		
		Matrix(std::initializer_list<std::initializer_list<Numeric>> list);
		Matrix(std::initializer_list<Vector<N, Numeric>> list);
		
	public:
		using Base_t = Geometry::Vector<M, Geometry::Vector<N, Numeric>>;
		Base_t comp;
		
	public:
		
		Matrix& transpose();
		static Matrix transpose(Matrix m);
		
		template<int O>
		Matrix<M,O,Numeric> operator * (Matrix<N,O,Numeric> r);
		
	};

}

#include "Matrix.hpp"

#endif /* MATRIX_H */
