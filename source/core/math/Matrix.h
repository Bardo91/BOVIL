/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-03
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BOVIL_CORE_MATH_MATRIX_H_
#define _BOVIL_CORE_MATH_MATRIX_H_

#include <cassert>
#include <iostream>
#include <cmath>
#include <sstream>

namespace BOViL{
	namespace math{
		//-----------------------------------------------------------------------------
		template <typename type_> 
		class Matrix{
		public:		// Main interface
			Matrix();		// Default constructor
			Matrix(int _cols, int _rows);		// Empty matrix constructor
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
			type_& operator[](int _index);
			void operator=(const Matrix& _mat);				// Assignement operator
			Matrix operator+(const Matrix& _mat) const;		// Add operator
			Matrix operator-(const Matrix& _mat) const;		// Sub operator
			Matrix operator*(const Matrix& _mat) const;		// Mul operator
			Matrix operator*(const type_ _scalar) const;		// Scalar operator
			Matrix operator&(const Matrix& _mat) const;		// Projection operator._mat is projected to this
			Matrix operator!();								// Transpose operator
			type_ operator~();								// Determinant operator
			Matrix operator^(const double _exp) const;		// Pow operator     666 TODO:

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
		Matrix<type_>::Matrix(){
			
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_>::Matrix(int _cols, int _rows):	mPtr(new type_[_cols*_rows]()),
														mCols(_cols),
														mRows(_rows)		
		{}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_>::Matrix(const type_* _matPtr, int _rows, int _cols):	mPtr(new type_[_cols*_rows]()),
																			mCols(_cols),
																			mRows(_rows)		
		{
			for(int i = 0; i < _cols*_rows ; i ++){
				mPtr[i] = _matPtr[i];
			}
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_>::Matrix(const Matrix<type_>& _mat):	mPtr(new type_[_mat.mCols*_mat.mRows]()),
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
		type_& Matrix<type_>::operator[](int _index){
			return mPtr[_index];
		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		void Matrix<type_>::operator= (const Matrix<type_>& _mat){
			mRows = _mat.mRows;
			mCols = _mat.mCols;
			
			if(mPtr)
				delete mPtr;

			mPtr = new type_[mRows*mCols]();

			for(int i = 0 ; i < mRows*mCols ; i++){
				mPtr[i] = _mat.mPtr[i];
			}
						
			return ;


		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_> Matrix<type_>::operator+ (const Matrix<type_>& _mat) const{
			if(_mat.mCols != mCols || _mat.mRows != mRows)
				assert(false);

			type_* ptr = new type_[_mat.mRows*_mat.mCols]();

			for(int i = 0; i < mRows ; i ++ ){
				for(int j = 0 ; j < mCols ; j ++){
					ptr[mCols * i + j] = mPtr[mCols * i + j] + _mat.getMatrixPtr()[mCols * i + j];
				}
			}

			Matrix<type_> mat(ptr, mRows, mCols);
			delete[] ptr;

			return mat;
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_> Matrix<type_>::operator- (const Matrix<type_>& _mat) const{
			if(_mat.mCols != mCols || _mat.mRows != mRows)
				assert(false);

			type_* ptr = new type_[_mat.mRows*_mat.mCols]();

			for(int i = 0; i < mRows ; i ++ ){
				for(int j = 0 ; j < mCols ; j ++){
					ptr[mCols * i + j] = mPtr[mCols * i + j] - _mat.getMatrixPtr()[mCols * i + j];
				}
			}

			Matrix<type_> mat(ptr, mRows, mCols);
			delete ptr;

			return mat;
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_> Matrix<type_>::operator* (const Matrix<type_>& _mat) const{
			if(mCols !=_mat.mRows)
				assert(false);

			type_* ptr = new type_[mRows*_mat.mCols]();

			for(int i = 0; i < mRows ; i ++ ){
				for(int j = 0 ; j < mCols ; j ++){
					ptr[_mat.mCols * i + j] = 0;
					for(int k = 0 ; k < _mat.mRows ; k ++){
						ptr[_mat.mCols * i + j] += mPtr[mCols*i + k]*_mat.mPtr[_mat.mCols*k + j];
					}
				}
			}

			Matrix<type_> mat(ptr, mRows, _mat.mCols);
			delete ptr;

			return mat;
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_> Matrix<type_>::operator* (const type_ _scalar) const{
			type_* ptr = new type_[mRows*mCols]();

			for(int i = 0; i < mRows ; i ++ ){
				for(int j = 0 ; j < mCols ; j ++){
					ptr[mCols * i + j] = mPtr[mCols * i + j]*_scalar;
				}
			}

			Matrix<type_> mat(ptr, mRows, mCols);
			delete ptr;

			return mat;
		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		Matrix<type_> Matrix<type_>::operator&(const Matrix<type_>& _mat) const{
			// 666 TODO:
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_> Matrix<type_>::operator! () {
			
			type_* ptr = new type_[mRows*mCols]();

			for(int i = 0; i < mRows ; i ++ ){
				for(int j = 0 ; j < mCols ; j ++){
					ptr[j*mCols + i] = mPtr[i*mCols + j];
				}
			}

			Matrix<type_> mat(ptr, mRows, mCols);
			delete ptr;

			return mat;
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		type_ Matrix<type_>::operator~ () {
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

			_Q = !_Q;

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