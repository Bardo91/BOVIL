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


namespace BOViL{
	namespace math{
		//-----------------------------------------------------------------------------
		template <typename type_> 
		class Matrix{
		public:
			Matrix();
			Matrix(int _cols, int _rows);
			Matrix(type_* _mat, int _rows, int _cols);
			~Matrix();

			type_* getMatrixPtr() const;

			void showMatrix() const;

		public:
			std::string operator<<(const Matrix<type_>& _mat) const;
			void operator=(const Matrix& _mat);
			Matrix operator-(const Matrix& _mat) const;
			Matrix operator*(const Matrix& _mat) const;
			Matrix operator+(const Matrix& _mat) const;

		private:
			int mCols, mRows;
			type_* mPtr;

		};

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_>::Matrix(){
			
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_>::Matrix(int _cols, int _rows){
			mPtr = new type_[_cols*_rows];
			mCols = _cols;
			mRows = _rows;

		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_>::Matrix(type_* _matPtr, int _rows, int _cols){
			mPtr = new type_[_cols*_rows];
			mCols = _cols;
			mRows = _rows;

			for(int i = 0; i < _cols*_rows ; i ++){
				mPtr[i] = _matPtr[i];
			}

		}
		
		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_>::~Matrix(){
			delete[] mPtr;
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		type_* Matrix<type_>::getMatrixPtr() const{
			return mPtr;
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
		template<typename type_>
		std::string Matrix<type_>::operator<< (const Matrix<type_>& _mat) const{

		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		void Matrix<type_>::operator= (const Matrix<type_>& _mat){
			mRows = _mat.mRows;
			mCols = _mat.mCols;

			delete mPtr;

			mPtr = new type_[mRows*mCols];

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

			type_* ptr = new type_[_mat.mRows*_mat.mCols];

			for(int i = 0; i < mRows ; i ++ ){
				for(int j = 0 ; j < mCols ; j ++){
					ptr[mCols * i + j] = mPtr[mCols * i + j] + _mat.getMatrixPtr()[mCols * i + j];
				}
			}

			Matrix<type_> mat(ptr, mRows, mCols);
			delete ptr;

			return mat;
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_> Matrix<type_>::operator- (const Matrix<type_>& _mat) const{
			if(_mat.mCols != mCols || _mat.mRows != mRows)
				assert(false);

			type_* ptr = new type_[_mat.mRows*_mat.mCols];

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

			type_* ptr = new type_[mRows*_mat.mCols];

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

		//-----------------------------------------------------------------------------
	}	// namespace math
}	// namespace BOViL


#endif	// _BOVIL_CORE_MATH_MATRIX_H_