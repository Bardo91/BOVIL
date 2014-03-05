/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-03
//
/////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <iostream>


namespace BOViL{
	namespace math{
		//-----------------------------------------------------------------------------
		template <typename type_> 
		class Matrix{
		public:
			Matrix(int _cols, int _rows);
			~Matrix();

			type_* getMatrix() const;

			void showMatrix() const;

		public:
			void operator<<(type_* _array);
			Matrix& operator=(const Matrix& _mat) const;
			Matrix& operator+(const Matrix& _mat) const;
			Matrix& operator-(const Matrix& _mat) const;
			Matrix& operator*(const Matrix& _mat) const;

		private:
			int mCols, mRows;
			type_* mPtr;

		};

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_>::Matrix(int _cols, int _rows){
			mPtr = new type_[_cols*_rows];
			mCols = _cols;
			mRows = _rows;
		}
		
		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_>::~Matrix(){
			delete[] mPtr;
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		type_* Matrix<type_>::getMatrix() const{
			return mPtr;
		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		void Matrix<type_>::showMatrix() const{
			std::cout << "[ ";

			for(int i = 0 ; i < mRows ; i++){
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
		void Matrix<type_>::operator<<(type_* _array) {
			// 666 TODO: check size.
			for(int i = 0 ; i < mRows*mCols ; i++){
				mPtr[i] = _array[i];
			}
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_>& Matrix<type_>::operator=(const Matrix& _mat) const{
			return this;
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_>& Matrix<type_>::operator+(const Matrix& _mat) const{
			if(_mat.mCols != mCols || _mat.mRows != mRows)
				assert(false);

		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_>& Matrix<type_>::operator-(const Matrix& _mat) const{
			return getMatrix();
		}

		//-----------------------------------------------------------------------------
		template<typename type_> 
		Matrix<type_>& Matrix<type_>::operator*(const Matrix& _mat) const{
			return getMatrix();
		}


		//-----------------------------------------------------------------------------


		//-----------------------------------------------------------------------------
	}	// namespace math
}	// namespace BOViL