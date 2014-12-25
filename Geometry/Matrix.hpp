/*
 * File:   Matrix.hpp
 * Author: Elias Forsberg
 *
 * Creadted on December 23, 2014, 21:56
 */

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Matrix.h"

using Geometry::Matrix;
using Geometry::Vector;

template<int M, int N, typename Numeric>
Matrix<M, N, Numeric>::Matrix():
	comp{}
{}

template<int M, int N, typename Numeric>
Matrix<M, N, Numeric>::Matrix(std::initializer_list<Vector<N, Numeric>> list) {
	int i = 0;
	for(auto n : list){
		comp[i] = n;
		i++;
	}
}

template<int M, int N, typename Numeric>
Matrix<M, N, Numeric>::Matrix (std::initializer_list<std::initializer_list<Numeric>> list) {
	int i = 0;
	for(auto a : list){
		comp[i] = Vector<N, Numeric>(a);
		i++;
	}
}

template<int M, int N, typename Numeric>
Matrix<M, N, Numeric>& Matrix<M, N, Numeric>::transpose() {
	Matrix<M, N, Numeric> res;
	for(int m = 0; m < M; m++){
		for(int n = 0; n < N; n++){
			res.comp[m][n] = comp[n][m];
		}
	}
	(*this) = res;
	return *this;
}

template<int P, int Q, typename T>
std::ostream& operator << (std::ostream& out, Matrix<P,Q,T> m){
	out << m.comp;
	return out;
}

#endif /* MATRIX_HPP */
