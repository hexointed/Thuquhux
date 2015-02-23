/*
 * File:   Matrix.hpp
 * Author: Elias Forsberg
 *
 * Creadted on December 23, 2014, 21:56
 */

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Matrix.h"
#include <math.h>

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
	Col_t res{};
	for(int k = 0; k < M; k++){
		res[k] = (*this)[k][i];
	}
	return res;
}

template<int M, int N, typename Num>
Num& Matrix<M,N,Num>::get(int r, int c) {
	return (*this)[r][c];
}

template<int M, int N, typename Num>
Num Matrix<M,N,Num>::get(int r, int c) const {
	return (*this)[r][c];
}

template<int M, int N, typename Num>
Matrix<M,N,Num>& Matrix<M,N,Num>::add(Matrix<M,N,Num> a){
	for(int m = 0; m < M; m++){
		for(int n = 0; n < N; n++){
			(*this)[m][n] += a[m][n];
		}
	}
	return *this;
}

template<int M, int N, typename Num>
Matrix<M,N,Num>& Matrix<M,N,Num>::add_comp(Num a){
	for(int m = 0; m < M; m++){
		for(int n = 0; n < N; n++){
			(*this)[m][n] += a;
		}
	}
	return (*this);
}

template<int M, int N, typename Num>
Matrix<M,N,Num> Matrix<M,N,Num>::add(Matrix<M,N,Num> a, Matrix<M,N,Num> b){
	return a.add(b);
}

template<int M, int N, typename Num>
Matrix<M,N,Num> Matrix<M,N,Num>::add_comp(Matrix<M,N,Num> a, Num b){
	return a.add_comp(b);
}

template<int M, int N, typename Num>
Matrix<M,N,Num>& Matrix<M,N,Num>::sub(Matrix<M,N,Num> a){
	for(int m = 0; m < M; m++){
		for( int n = 0; n < N; n++){
			(*this)[m][n] -= a[m][n];
		}
	}
	return *this;
}

template<int M, int N, typename Num>
Matrix<M,N,Num>& Matrix<M,N,Num>::sub_comp(Num a){
	for(int m = 0; m < M; m++){
		for(int n = 0; n < N; n++){
			(*this)[m][n] -= a;
		}
	}
	return *this;
}

template<int M, int N, typename Num>
Matrix<M,N,Num> Matrix<M,N,Num>::sub(Matrix<M,N,Num> a, Matrix<M,N,Num> b){
	return a.sub(b);
}

template<int M, int N, typename Num>
Matrix<M,N,Num> Matrix<M,N,Num>::sub_comp(Matrix<M,N,Num> a, Num b){
	return a.sub_comp(b);
}

template<int M, int N, typename Num>
Matrix<M,N,Num>& Matrix<M,N,Num>::mul(Num a){
	for(int m = 0; m < M; m++){
		for(int n = 0; n < N; n++){
			(*this)[m][n] *= a;
		}
	}
	return *this;
}

template<int M, int N, typename Num>
Matrix<M,N,Num>& Matrix<M,N,Num>::mul_comp(Matrix<M,N,Num> a){
	for(int m = 0; m < M; m++){
		for(int  n = 0; n < N; n++){
			(*this)[m][n] *= a[m][n];
		}
	}
	return *this;
}

template<int M, int N, typename Num>
Matrix<M,N,Num> Matrix<M,N,Num>::mul(Matrix<M,N,Num> a, Num b){
	return a.mul(b);
}

template<int M, int N, typename Num>
Matrix<M,N,Num> Matrix<M,N,Num>::mul_comp(Matrix<M,N,Num> a, Matrix<M,N,Num> b){
	return a.mul_comp(b);
}

template<int M, int N, typename Num>
Matrix<M,N,Num>& Matrix<M,N,Num>::mul(Matrix<N,M,Num> a){
	Matrix<M,N,Num> res{};
	for(int m = 0; m < M; m++){
		for(int n = 0; n < N; n++){
			res[m][n] = Row_t::mul_dot((*this)[m], a.get_col(n));
		}
	}
	return (*this) = res;
}

template<int M, int N, typename Num>
template<int O>
Matrix<M,O,Num> Matrix<M,N,Num>::mul(Matrix<M,N,Num> a, Matrix<N,O,Num> b){
	Matrix<M,O,Num> res{};
	for(int m = 0; m < M; m++){
		for(int o = 0; o < O; o++){
			res[m][o] = Row_t::mul_dot(a[m], b.get_col(o));
		}
	}
	return res;
}

template<int M, int N, typename Num>
Matrix<M,N,Num>& Matrix<M,N,Num>::div(Num a) {
	for(int m = 0; m < M; m++) {
		for(int n = 0; n < N; n++){
			(*this)[m][n] /= a;
		}
	}
	return *this;
}

template<int M, int N, typename Num>
Matrix<M,N,Num>& Matrix<M,N,Num>::div_comp(Matrix<M,N,Num> a){
	for(int m = 0; m < M; m++) {
		for(int n = 0; n < N; n++) {
			(*this)[m][n] /= a[m][n];
		}
	}
	return *this;
}

template<int M, int N, typename Num>
Matrix<M,N,Num>& Matrix<M,N,Num>::pow_comp(Num a){
	for(int m = 0; m < M; m++){
		for(int n = 0; n < N; n++){
			(*this)[m][n] = pow((*this)[m][n], a);
		}
	}
	return *this;
}

template<int M, int N, typename Num>
Matrix<M,N,Num> Matrix<M,N,Num>::pow_comp(Matrix<M,N,Num> a, Num b){
	return a.pow_comp(b);
}

template<int M, int N, typename Num>
template<typename Functor>
Matrix<M,N,Num>& Matrix<M,N,Num>::op_comp(Functor f){
	for(int m = 0; m < M; m++){
		for(int n = 0; n < N; n++){
			(*this)[m][n] = f((*this)[m][n]);
		}
	}
	return *this;
}

template<int M, int N, typename Num>
template<typename Functor>
Matrix<M,N,Num>& Matrix<M,N,Num>::op_comp(Matrix<M,N,Num> a, Functor f){
	for(int n = 0; n < N; n++){
		for(int m = 0; m < M; m++){
			(*this)[m][n] = f((*this)[m][n], a[m][n]);
		}
	}
	return *this;
}

template<int M, int N, typename Num>
Num Matrix<M,N,Num>::sum_comp() const {
	Num res{};
	for(int m = 0; m < M; m++){
		for(int n = 0; n < N; n++){
			res += (*this)[m][n];
		}
	}
	return res;
}

template<int M, int N, typename Num>
typename Matrix<M,N,Num>::Row_t Matrix<M,N,Num>::sum_rows() const {
	typename Matrix<M,N,Num>::Row_t res{};
	for(int m = 0; m < M; m++){
		res += this->get_row(m);
	}
	return res;
}

template<int M, int N, typename Num>
typename Matrix<M,N,Num>::Col_t Matrix<M,N,Num>::sum_cols() const {
	typename Matrix<M,N,Num>::Col_t res{};
	for(int n = 0; n < N; n++){
		res += this->get_col(n);
	}
	return res;
}

template<int M, int N, typename Num>
Matrix<M-1,N-1,Num> Matrix<M,N,Num>::minor_matrix(int x, int y) const {
	Matrix<M-1,N-1,Num> res{};
	for(int m = 0; m < M; m++){
		for(int n = 0; n < N; n++){
			if(m == x || n == y) continue;
			res[m < x ? m : m-1][n < y ? n : n-1] = (*this)[m][n];
		}
	}
	return res;
}

template<int M, int N, typename Numeric>
Matrix<M, N, Numeric>& Matrix<M, N, Numeric>::transpose() {
	static_assert(M==N, "Cannot assign matrix to it's transpose because matrix dimensions are not equal.");
	Matrix<M, N, Numeric> res{};
	for(int m = 0; m < M; m++){
		for(int n = 0; n < N; n++){
			res[m][n] = (*this)[n][m];
		}
	}
	(*this) = res;
	return *this;
}

template<int M, int N, typename Num>
Matrix<M,N,Num>& Matrix<M,N,Num>::cofactor() {
	static_assert(M==N, "Cofactor matrix only defined for square matricies.");
	Matrix<M,N,Num> res{};
	for(int m = 0; m < M; m++){
		for(int n = 0; n < N; n++){
			res[m][n] = this->minor_matrix(m,n).determinant();
		}
	}
	res.mul_comp(Matrix<M,N,Num>::checkerboard());
	return (*this)=res;
}

#include <iostream>

template<int M, int N, typename Num>
Matrix<M,N,Num>& Matrix<M,N,Num>::inverse() {
	static_assert(M==N, "Inverse only defined for square matricies.");
	Matrix<M,N,Num> res = *this;
	res.cofactor().transpose();
	Num det = this->determinant();
	std::cout<<det<<std::endl;
	res.op_comp([&det] (Num a) {
		return a/det;
	});
	return (*this) = res;
}

class Det {
public:
	template<int M, int N, typename Num>
	static Num det(Matrix<M,N,Num> m){
		Num res{};
		for(int i = 0; i < M; i++){
			res += m[i][0] * det(m.minor_matrix(i,0)) * (i%2 ? -1 : 1);
		}
		return res;
	}
	template<typename Num>
	static Num det(Matrix<1,1,Num> m){
		return m[0][0];
	}
};

template<int M, int N, typename Num>
Num Matrix<M,N,Num>::determinant() const {
	static_assert(M==N, "Determinant only defined for square matricies.");
	return Det::det(*this);
}

template<int M, int N, typename Num>
Num Matrix<M,N,Num>::trace() const {
	constexpr int D = M < N ? M : N;
	Num res{};
	for(int d = 0; d < D; d++){
		res += (*this)[d][d];
	}
	return res;
}

template<int M, int N, typename Num>
Matrix<N, M, Num> Matrix<M, N, Num>::transpose(Matrix<M, N, Num> a){
	Matrix<N,M,Num> res{};
	for(int m = 0; m < M; m++){
		for(int n = 0; n < N; n++){
			res[n][m] = a[m][n];
		}
	}
	return res;
}

template<int M, int N, typename Num>
Matrix<M,N,Num> Matrix<M,N,Num>::cofactor(Matrix<M,N,Num> a){
	return a.cofactor();
}

template<int M, int N, typename Num>
Matrix<M,N,Num> Matrix<M,N,Num>::inverse(Matrix<M,N,Num> a) {
	return a.inverse();
}

template<int M, int N, typename Num>
Num Matrix<M,N,Num>::determinant(Matrix<M,N,Num> a){
	return a.determinant();
}

template<int M, int N, typename Num>
Num Matrix<M,N,Num>::trace(Matrix<M,N,Num> a) {
	return a.trace();
}

template<int M, int N, typename Num>
Matrix<M,N,Num>& Matrix<M,N,Num>::set_min_comp(Matrix<M,N,Num> a){
	for(int m = 0; m < M; m++){
		for(int n = 0; n < N; n++){
			(*this)[m][n] = (*this)[m][n] < a[m][n] ? (*this)[m][n] : a[m][n];
		}
	}
	return *this;
}

template<int M, int N, typename Num>
Matrix<M,N,Num>& Matrix<M,N,Num>::set_max_comp(Matrix<M,N,Num> a){
	for(int m = 0; m< M; m++){
		for(int n = 0; n< N; n++){
			(*this)[m][n] = (*this)[m][n] > a[m][n] ? (*this)[m][n] : a[m][n];
		}
	}
	return *this;
}

template<int M, int N, typename Num>
Matrix<M,N,Num> Matrix<M,N,Num>::min_comp(Matrix<M,N,Num> a, Matrix<M,N,Num> b){
	return a.set_min_comp(b);
}

template<int M, int N, typename Num>
Matrix<M,N,Num> Matrix<M,N,Num>::max_comp(Matrix<M,N,Num> a, Matrix<M,N,Num> b){
	return a.set_max_comp(b);
}

template<int M, int N, typename Num>
bool Matrix<M,N,Num>::is_min_comp(Matrix<M,N,Num> a){
	for(int m = 0; m < M; m++){
		for(int n = 0; n < N; n++){
			if((*this)[m][n] >= a[m][n]) return false;
		}
	}
	return true;
}

template<int M, int N, typename Num>
bool Matrix<M,N,Num>::is_max_comp(Matrix<M,N,Num> a){
	for(int m = 0; m < M; m++){
		for(int n = 0; n < N; n++){
			if((*this)[m][n] <= a[m][n]) return false;
		}
	}
	return true;
}

template<int M, int N, typename Num>
bool Matrix<M,N,Num>::is_eq_comp(Matrix<M,N,Num> a){
	for(int m = 0; m < M; m++){
		for(int n = 0; n < N; n++){
			if((*this)[m][n] == a[m][n]) return false;
		}
	}
	return true;
}

template<int M, int N, typename Num>
Matrix<M,N,Num> Matrix<M,N,Num>::identity() {
	static_assert(M==N, "Identity matrix only defined for square matricies");
	Matrix<M,N,Num> res{};
	for(int n = 0; n < N; n++){
		res[n][n] = Num{1};
	}
	return res;
}

template<int M, int N, typename Num>
Matrix<M,N,Num> Matrix<M,N,Num>::checkerboard() {
	Matrix<M,N,Num> res{};
	for(int m = 0; m < M; m++){
		for(int n = 0; n < N; n++){
			if((m+n)%2){
				res[m][n] = Num{-1};
			} else {
				res[m][n] = Num{1};
			}
		}
	}
	return res;
}

template<int M, int N, typename Numeric>
template<int O>
Matrix<M,O,Numeric> Matrix<M,N,Numeric>::operator* (Matrix<N,O,Numeric> m) {
	Matrix<M,O,Numeric> res{};
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
	out << m._;
	return out;
}

#endif /* MATRIX_HPP */