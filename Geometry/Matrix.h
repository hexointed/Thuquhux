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

#include "Geometry.h"

namespace Geometry {
	
	/*
	 * M is the number of rows, N is the number of columns. Numeric is the type
	 * of the elements in the Matrix. In order for this class to be fully 
	 * usable, Numeric should overload all arithmetic and comparison operators.
	 * It should also be default-constructible and copy-assignable. Iff Numeric
	 * is POD, Matrix is POD.
	 */
	
	template<int M, int N, typename Numeric = double>
	class Matrix {
	public:
		Matrix() = default;
		
	public:
		using Row_t = Geometry::Vector<N, Numeric>;
		using Col_t = Geometry::Vector<M, Numeric>;
		using Base_t = Geometry::Vector<M, Row_t>;
		
	public:
		/*
		 * Some methods for accessing the rows, columns and elements of the 
		 * Matrix.
		 */
		
		Row_t& operator [] (int i);
		Row_t operator [] (int i) const;
		
		Row_t& get_row(int i);
		Row_t get_row(int i) const;
		
		Col_t get_col(int i) const;
		
		Numeric& get(int r, int c);
		Numeric get(int r, int c) const;
		
		/*
		 * Some common arithmetic operations.
		 */
		
		Matrix add (Matrix m) const;
		Matrix add_comp (Numeric n) const;
		static Matrix add (Matrix l, Matrix r);
		static Matrix add_comp (Matrix m, Numeric n);
		
		Matrix sub (Matrix m) const;
		Matrix sub_comp (Numeric n) const;
		static Matrix sub (Matrix l, Matrix r);
		static Matrix sub_comp (Matrix m, Numeric n);
		
		template<int O>
		Matrix<M,O,Numeric> mul (Matrix<N,O,Numeric> m) const;
		Matrix mul (Numeric n) const;
		Matrix mul_comp (Matrix m) const;
		static Matrix mul (Matrix m, Numeric n);
		static Matrix mul_comp (Matrix l, Matrix r);
		template<int O>
		static Matrix<M,O,Numeric> mul (Matrix<M,N,Numeric> a, Matrix<N,O,Numeric> b);

		Matrix div (Numeric n) const;
		Matrix div_comp (Matrix m) const;
		static Matrix div (Matrix m, Numeric n);
		static Matrix div_comp (Matrix l, Matrix r);
		
		Matrix pow_comp (Numeric n) const;
		static Matrix pow_comp (Matrix m, Numeric n);
		
		Matrix mod (Numeric n) const;
		Matrix mod_comp (Matrix m) const;
		static Matrix mod (Matrix m, Numeric n);
		static Matrix mod_comp (Matrix m, Matrix n);
		
		template<typename Functor>
		Matrix op_comp (Functor f) const;
		template<typename Functor>
		Matrix op_comp (Matrix m, Functor f) const;
		
		Numeric sum_comp () const;
		Row_t   sum_rows () const;
		Col_t   sum_cols () const;
		
		/*
		 * Common, matrix-specific arithmetic operations.
		 */
		
		Matrix<M-1,N-1,Numeric> minor_matrix (int x, int y) const;
		Matrix<N,M,Numeric> transpose () const;
		Matrix cofactor () const;
		Matrix<N,M,Numeric> adjoint () const;
		Matrix inverse () const;
		Numeric determinant () const;
		Numeric trace () const;
		static Matrix<N,M,Numeric> transpose (Matrix m);
		static Matrix cofactor (Matrix m);
		static Matrix<N,M,Numeric> adjoint (Matrix m);
		static Matrix inverse (Matrix m);
		static Numeric determinant (Matrix m);
		static Numeric trace (Matrix m);
		
		/*
		 * Overloaded operators.
		 */
		/*
		 * a is considered max_comp(b) if all elements in a are equal to or 
		 * bigger than their respective element in b.
		 */
		
		Matrix& set_min_comp (Matrix m);
		Matrix& set_max_comp (Matrix m);
		Matrix min_comp (Matrix m);
		Matrix max_comp (Matrix m);
		static Matrix min_comp (Matrix l, Matrix r);
		static Matrix max_comp (Matrix l, Matrix r);
		
		bool is_min_comp (Matrix m);
		bool is_max_comp (Matrix m);
		bool is_eq_comp (Matrix m);
		
		/*
		 * Some useful constant matricies.
		 */
		
		static Matrix identity();
		static Matrix checkerboard();
		
		/*
		 * Iterators, for use with range-based for-loops. (Or other things, if
		 * you're into that stuff).
		 */
		
		using Row_Iterator = Row_t*;
		using Element_Iterator = Numeric*;
		
		/*
		 * _ should probably not be used outside this class, it is made public
		 * to make the class POD, because this results in better compiler 
		 * optimizations.
		 */
	public:
		Base_t _;
	};

}

#include "Matrix.hpp"

#endif /* MATRIX_H */
