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
		
		Matrix& add (Matrix m);
		Matrix& add_comp (Numeric n);
		static Matrix add (Matrix l, Matrix r);
		static Matrix add_comp (Matrix m, Numeric n);
		
		Matrix& sub (Matrix m);
		Matrix& sub_comp (Numeric n);
		static Matrix sub (Matrix l, Matrix r);
		static Matrix sub_comp (Matrix m, Numeric n);
		
		Matrix& mul (Matrix<N,M,Numeric> m);
		Matrix& mul (Numeric n);
		Matrix& mul_comp (Matrix m);
		static Matrix mul (Matrix m, Numeric n);
		static Matrix mul_comp (Matrix l, Matrix r);
		
		template<int O>
		static Matrix<M,O,Numeric> mul (Matrix<M,N,Numeric> a, Matrix<N,O,Numeric> b);

		Matrix& div (Numeric n);
		Matrix& div_comp (Matrix m);
		static Matrix div (Matrix m, Numeric n);
		static Matrix div_comp (Matrix l, Matrix r);
		
		Matrix& pow_comp (Numeric n);
		static Matrix pow_comp (Matrix m, Numeric n);
		
		template<typename Functor>
		Matrix& op_comp (Functor f);
		template<typename Functor>
		Matrix& op_comp (Matrix m, Functor f);
		
		Numeric sum_comp () const;
		Row_t   sum_rows () const;
		Col_t   sum_cols () const;
		
		/*
		 * Common, matrix-specific arithmetic operations.
		 */
		
		Matrix<M-1,N-1,Numeric> minor_matrix (int x, int y) const;
		Matrix& transpose ();
		Matrix& cofactor ();
		Matrix& inverse ();
		Numeric determinant () const;
		Numeric trace () const;
		static Matrix<N,M,Numeric> transpose (Matrix m);
		static Matrix cofactor (Matrix m);
		static Matrix inverse (Matrix m);
		static Numeric determinant (Matrix m);
		static Numeric trace (Matrix m);
		
		/*
		 * Overloaded operators.
		 */
		
		Matrix operator + (Matrix r);
		Matrix operator - (Matrix r);
		Matrix operator * (Numeric r);
		Matrix operator / (Numeric r);
		
		Matrix& operator += (Matrix r);
		Matrix& operator -= (Matrix r);
		Matrix& operator *= (Numeric r);
		Matrix& operator /= (Numeric r);
		
		template<int O>
		Matrix<M,O,Numeric> operator * (Matrix<N,O,Numeric> r);
		
		/*
		 * a is considered max_comp(b) if all elements in a are equal to or 
		 * bigger than their respective element in b.
		 */
		
		Matrix& set_min_comp (Matrix m);
		Matrix& set_max_comp (Matrix m);
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
