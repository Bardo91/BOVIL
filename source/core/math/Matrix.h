/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Ram�n Soria
//		Date:	2014-05-03
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BOVIL_CORE_MATH_MATRIX_H_
#define _BOVIL_CORE_MATH_MATRIX_H_

#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>

namespace BOViL{
	namespace math{
		//-----------------------------------------------------------------------------
		template <typename type_> 
		class Matrix{
		public:		// Main interface
			Matrix();		// Default constructor
			Matrix(int _rows, int _cols);		// Empty matrix constructor
			Matrix(const type_* _mat, int _rows, int _cols);	// Full-defined matrix constructor
			Matrix(const Matrix& _mat);		// Copy constructor
			Matrix(Matrix&& _mat);			// Move constructor c++11

			~Matrix();		// De-constructor

			type_* getMatrixPtr() const;
			int getWidth() const;
			int getHeight() const;

			void showMatrix() const;

		public:	// Overloaded Operators
			std::string operator<<(const Matrix<type_>& _mat) const;		// Operator for cout 666 TODO:
			type_& operator[](const int _index) const;
			type_& operator()(const int _i, const int _j);
			const type_& operator()(const int _i, const int _j) const;
			Matrix operator=(const Matrix& _mat);				// Assignement operator
			Matrix operator+(const Matrix& _mat) const;		// Add operator
			Matrix operator-(const Matrix& _mat) const;		// Sub operator
			Matrix operator*(const Matrix& _mat) const;		// Mul operator
			Matrix operator*(const type_ _scalar) const;		// Scalar operator
			Matrix operator^(const double _exp) const;		// Pow operator     666 TODO:

		public:	// Other operations	666 TODO: Change names
			Matrix operator&(const Matrix& _mat) const;		// Projection operator._mat is projected to this
			Matrix transpose();								// Transpose operator
			type_ determinant();							// Determinant operator

		public:		// Various algorithms
			double norm();
			bool decompositionLU(Matrix& _L, Matrix& _U);
			bool decompositionCholesky(Matrix& _L, Matrix& _Lt);
			bool decompositionLDL(Matrix& _L, Matrix& _D, Matrix& _Lt);
			bool decompositionQR_GR(Matrix& _Q, Matrix& _R);		// QR decomposition using Householder reflexions algorithm.

			Matrix inverse();		// Using QR algorithm
			

		private:	// Private interface
			int mCols, mRows;
			type_* mPtr;

		};
		
		//-----------------------------------------------------------------------------
		//-------------------------- Related functions -------------------------------
		//-----------------------------------------------------------------------------
		template<typename type_>
		Matrix<type_> createEye(int _n){
			Matrix<type_> mat(_n, _n);

			for(int i = 0 ; i < _n ; i++){
				mat[i * _n + i] = 1;
			}

			return mat;
		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		Matrix<type_> createGivenRotation(int _n, int _i, int _j, double _theta){
			Matrix<type_>  mat = createEye<type_>(_n);

			mat[_i*_n + _i] = cos(_theta);
			mat[_j*_n + _j] = cos(_theta);
			mat[_i*_n + _j] = sin(_theta);
			mat[_j*_n + _i] = -sin(_theta);
			
			return mat;
		}

		//-----------------------------------------------------------------------------
		//---------------------- Matrix Main interface -------------------------------
		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_>::Matrix():	mCols(0),
									mRows(0),
									mPtr(nullptr){
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_>::Matrix(int _rows, int _cols):	mPtr(new type_[_cols*_rows]),
														mCols(_cols),
														mRows(_rows)	{
			memset(mPtr, 0, sizeof(type_) * _cols * _rows);
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_>::Matrix(const type_* _matPtr, int _rows, int _cols):	mPtr(new type_[_cols*_rows]),
																			mCols(_cols),
																			mRows(_rows)		
		{
			for(int i = 0; i < _cols*_rows ; i ++){
				mPtr[i] = _matPtr[i];
			}
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_>::Matrix(const Matrix<type_>& _mat):	mPtr(new type_[_mat.mCols*_mat.mRows]),
															mCols(_mat.mCols),
															mRows(_mat.mRows) {
			for(int i = 0; i < mCols*mRows ; i ++){
				mPtr[i] = _mat.mPtr[i];
			}
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_>::Matrix(Matrix<type_>&& _mat):	mPtr(_mat.mPtr),
														mCols(_mat.mCols),
														mRows(_mat.mRows){
			_mat.mPtr = nullptr;
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_>::~Matrix(){
			if(mPtr)
				delete[] mPtr;
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		type_* Matrix<type_>::getMatrixPtr() const{
			return mPtr;
		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		int Matrix<type_>::getWidth() const{
			return mCols;
		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		int Matrix<type_>::getHeight() const{
			return mRows;
		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		void Matrix<type_>::showMatrix() const{
			std::cout << "[ ";

			for(int i = 0 ; i < mRows ; i++){
				std::cout << "\t";
				for(int j = 0 ; j < mCols ; j++){
					std::cout << mPtr[i*mCols + j] << "  ";;
				}
				if(i < mRows - 1)
					std::cout << " ;" << std::endl;
			}
			std::cout << " ]" << std::endl;
		}

		//-----------------------------------------------------------------------------
		//------------------------ Overloaded operators ------------------------------
		//-----------------------------------------------------------------------------
		template<typename type_>
		std::string Matrix<type_>::operator<< (const Matrix<type_>& _mat) const{
			
			std::stringstream ss;

			ss << "[ ";

			for(int i = 0 ; i < mRows ; i++){
				ss << "\t";
				for(int j = 0 ; j < mCols ; j++){
					ss << mPtr[i*mCols + j] << "  ";;
				}
				if(i < mRows - 1)
					ss << " ;" << std::endl;
			}
			ss << " ]" << std::endl;

			return ss.str();

		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		type_& Matrix<type_>::operator[](int _index) const{
			return mPtr[_index];
		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		type_& Matrix<type_>::operator()(int _i, int _j){
			return mPtr[_i * mCols + _j];
		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		const type_& Matrix<type_>::operator()(int _i, int _j) const{
			return mPtr[_i * mCols + _j];
		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		Matrix<type_> Matrix<type_>::operator= (const Matrix<type_>& _mat){
			if(this != &_mat){
				if(mRows != _mat.mRows || mCols != _mat.mCols){
					if(mPtr)
						delete[] mPtr;
					mRows = _mat.mRows;
					mCols = _mat.mCols;

					mPtr = new type_[mRows*mCols];
				}
				for(int i = 0 ; i < mCols*mRows ; i++){
					mPtr[i] = _mat.mPtr[i];
				}
			}
			return *this;
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_> Matrix<type_>::operator+ (const Matrix<type_>& _mat) const{
			assert(_mat.mCols == mCols || _mat.mRows == mRows);

			Matrix<type_> mat(mRows, mCols);

			for(int i = 0; i < mRows ; i ++ ){
				for(int j = 0 ; j < mCols ; j ++){
					mat(i, j) = (*this)(i, j) + _mat(i, j);
				}
			}

			return mat;
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_> Matrix<type_>::operator- (const Matrix<type_>& _mat) const{
			assert(_mat.mCols == mCols || _mat.mRows == mRows);

			Matrix<type_> mat(mRows, mCols);

			for(int i = 0; i < mRows ; i ++ ){
				for(int j = 0 ; j < mCols ; j ++){
					mat(i, j) = (*this)(i, j) - _mat(i, j);
				}
			}

			return mat;
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_> Matrix<type_>::operator* (const Matrix<type_>& _mat) const{
			assert(mCols ==_mat.mRows);

			Matrix<type_> mat(mRows, _mat.mCols);

			for(int i = 0; i < mat.mRows ; i ++ ){
				for(int j = 0 ; j < mat.mCols ; j ++){
					mat(i, j) = 0;
					for(int k = 0 ; k < mCols ; k ++){
						mat(i, j) += (*this)(i, k) * _mat(k, j);
					}
				}
			}

			return mat;
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_> Matrix<type_>::operator* (const type_ _scalar) const{

			Matrix<type_> mat(mRows, mCols);

			for(int i = 0; i < mRows ; i ++ ){
				for(int j = 0 ; j < mCols ; j ++){
					mat(i, j) = (*this)(i, j) * _scalar;
				}
			}

			return mat;
		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		Matrix<type_> Matrix<type_>::operator^(const double _exp) const{
			Matrix<type_> mat(*this);

			if(_exp < 0){
				mat = mat^-_exp;
				mat = mat.inverse();
			} else {
				for(int i = 0 ; i < mRows ; i++){
					for(int j = 0 ; j < mCols ; j++){
						mPtr[i*mCols + j] = pow(mPtr[i*mCols + j], _exp);
					}
				}
			}

			return mat;

		}

		//-----------------------------------------------------------------------------
		//------------------------Other operators-------------------------------------
		//-----------------------------------------------------------------------------
		template<typename type_>
		Matrix<type_> Matrix<type_>::operator&(const Matrix<type_>& _mat) const{
			// 666 TODO:
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_> Matrix<type_>::transpose () {
			Matrix<type_> mat(mCols, mRows);

			for(int i = 0; i < mRows ; i ++ ){
				for(int j = 0 ; j < mCols ; j ++){
					mat(j, i) = (*this)(i, j);
				}
			}

			return mat;
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		type_ Matrix<type_>::determinant () {
			if(mCols == mRows){
				Matrix<type_> L(mRows, mCols), U(mRows, mCols);

				if(decompositionLU(L, U)){
					type_ det = U[0];
					for(int i = 1 ; i < mRows ; i++){
						det *= U[i*mRows + i];
					}
					return det;
				}
			}

			return static_cast<type_>(0);
		}

		//-----------------------------------------------------------------------------
		//-------------------------- Various algorithms -------------------------------
		//------------------------------------------------------------------------------
		template<typename type_>
		double Matrix<type_>::norm(){		// 666 TODO: only true if vector, if not, is not max norm
			int size = mRows > mCols ? mRows : mCols;

			double norm = 0;

			for(int i = 0 ; i < size ; i++){
				norm += mPtr[i]*mPtr[i];
			}

			return sqrt(norm);
		}

		//------------------------------------------------------------------------------
		template<typename type_>
		bool Matrix<type_>::decompositionLU(Matrix& _L, Matrix& _U){
			if(	_L.mCols != _U.mCols || _L.mCols != mCols ||
				_L.mRows != _U.mRows || _L.mRows != mRows){
				return false;	// Bad matrix sizes
			}

			_U = Matrix<type_>(mPtr, mRows, mCols);

			for(int i = 0 ; i < mRows ; i++){
				_L[i*mCols + i] = 1.0;	// Set de diagonals of L. Eye matrix
				for(int k = i + 1 ; k < mRows ; k++){
					_L[k*mCols + i] = _U[k*mCols + i] / _U[i*mCols + i];
					for(int j = 0 ; j < mCols ; j ++){
						_U[k*mCols + j] = _U[k*mCols + j] - _U[i*mCols + j] * _L[k*mCols + i];
					}
				}
			}

			return true;
		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		bool Matrix<type_>::decompositionQR_GR(Matrix<type_>& _Q, Matrix<type_>& _R){

			// 666 TODO: improve without for loop	
			int t = 0;
			for(int i = 1 ; i <= mRows ; i++){
				t += i;
			}
			if(mRows < mCols)
				t += (mRows - mCols) * mCols;

			int dim = mRows > mCols ? mRows : mCols;
			_R = *this;
			_Q = createEye<type_>(dim);

			// Creating Givens Rotation matrix
			for(int j = 0 ; j < mCols  ; j++){
				for(int i = mRows - 1;  i > j ; i--){
					double theta = atan(- _R[i*dim + j] / _R[(i - 1)*dim + j]);
					Matrix<type_> Gi = createGivenRotation<type_>(dim, i, i - 1, theta);
					
					_R = Gi * _R;
					_Q = Gi * _Q;
				}
			}

			_Q = _Q.transpose();

			return true;
		}
		//-----------------------------------------------------------------------------
		template<typename type_>
		Matrix<type_> Matrix<type_>::inverse(){
			// 666 TODO: how to do inverse? try with gaussian elimination
			if(mCols != mRows)
				assert(false);

			
			Matrix<type_> matInv = createEye<type_>(mRows), mat(*this);

			// Inferior triangle elimination.
			for(int i = 0 ; i < mRows ; i++){
				for(int k = i + 1 ; k < mRows ; k++){
					double factor = mat[k*mCols + i] / mat[i*mCols + i];
					for(int j = 0 ; j < mCols ; j ++){
						mat[k*mCols + j] = mat[k*mCols + j] - mat[i*mCols + j] * factor;
						matInv[k*mCols + j] = matInv[k*mCols + j] - matInv[i*mCols + j] * factor;
					}
				}
			}

			// Superior triangle elimination.
			for(int i = mRows - 1 ; i > 0 ; i--){
				for(int k = i - 1 ; k >= 0 ; k--){
					double factor = mat[k*mCols + i] / mat[i*mCols + i];
					for(int j = mCols - 1 ; j >= 0  ; j --){
						mat[k*mCols + j] = (mat[k*mCols + j] - mat[i*mCols + j] * factor);
						matInv[k*mCols + j] = (matInv[k*mCols + j] - matInv[i*mCols + j] * factor);
					}
				}

				for(int j = 0 ; j < mCols ; j ++){	// Unitarize the diagonal
					matInv[i*mCols + j] = matInv[i*mCols + j] / mat[i*mCols + i] ;
				}
			}

			return matInv;
		}
		//-----------------------------------------------------------------------------
	}	// namespace math
}	// namespace BOViL


#endif	// _BOVIL_CORE_MATH_MATRIX_H_