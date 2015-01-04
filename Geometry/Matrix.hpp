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

template<int M, int N, typename Num>
typename Matrix<M,N,Num>::Row_t& Matrix<M,N,Num>::operator [] (int i) {
	return _[i];
}

template<int M, int N, typename Num>
typename Matrix<M,N,Num>::Row_t Matrix<M,N,Num>::operator [] (int i) const {
	return _[i];
}

template<int M, int N, typename Num>
typename Matrix<M,N,Num>::Row_t& Matrix<M,N,Num>::get_row (int i) {
	return _[i];
}

template<int M, int N, typename Num>
typename Matrix<M,N,Num>::Row_t Matrix<M,N,Num>::get_row (int i) const {
	return _[i];
}

template<int M, int N, typename Num>
typename Matrix<M,N,Num>::Col_t Matrix<M,N,Num>::get_col (int i) const {
	Col_t res;
	for(int k = 0; k < M; k++){
		res[k] = (*this)[k][i];
	}
	return res;
}

template<int M, int N, typename Numeric>
Matrix<M, N, Numeric>& Matrix<M, N, Numeric>::transpose() {
	Matrix<M, N, Numeric> res;
	for(int m = 0; m < M; m++){
		for(int n = 0; n < N; n++){
			res[m][n] = (*this)[n][m];
		}
	}
	(*this) = res;
	return *this;
}

template<int M, int N, typename Numeric>
Matrix<M, N, Numeric> Matrix<M, N, Numeric>::transpose(Matrix<M, N, Numeric> m){
	return m.transpose();
}

template<int M, int N, typename Numeric>
template<int O>
Matrix<M,O,Numeric> Matrix<M,N,Numeric>::operator* (Matrix<N,O,Numeric> m) {
	Matrix<M,O,Numeric> res;
	auto t = m.transpose();
	for(int i = 0; i < M; i++){
		for(int j = 0; j < O; j++){
			res[i][j] = Base_t::Numeric_type::mul_dot((*this)[i], m[j]);
		}
	}
	return res;
}

template<int P, int Q, typename T>
std::ostream& operator << (std::ostream& out, Matrix<P,Q,T> m){
	out << m.comp;
	return out;
}

#endif /* MATRIX_HPP */
