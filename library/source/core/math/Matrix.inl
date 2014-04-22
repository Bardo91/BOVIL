/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Ramón Soria
//		Date:	2014-04-22
//
/////////////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
//---------------------- Matrix Main interface -------------------------------
//-----------------------------------------------------------------------------

#include "Matrix.h"

namespace BOViL{
	namespace math {
		template<typename type_>
		Matrix<type_>::Matrix() : mRows(0),
			mCols(0),
			mPtr(nullptr){
		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		Matrix<type_>::Matrix(int _rows, int _cols) : mRows(_rows),
			mCols(_cols),
			mPtr(new type_[_cols*_rows])	{
			memset(mPtr, 0, sizeof(type_)* _cols * _rows);
		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		Matrix<type_>::Matrix(const type_* _matPtr, int _rows, int _cols) : mRows(_rows),
			mCols(_cols),
			mPtr(new type_[_cols*_rows])	{
			for (int i = 0; i < _cols*_rows; i++){
				mPtr[i] = _matPtr[i];
			}
		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		Matrix<type_>::Matrix(const Matrix<type_>& _mat) : mRows(_mat.mRows),
			mCols(_mat.mCols),
			mPtr(new type_[_mat.mCols*_mat.mRows]) {
			for (int i = 0; i < mCols*mRows; i++){
				mPtr[i] = _mat.mPtr[i];
			}
		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		Matrix<type_>::Matrix(Matrix<type_>&& _mat) : mRows(_mat.mRows),
			mCols(_mat.mCols),
			mPtr(_mat.mPtr){
			_mat.mPtr = nullptr;
		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		Matrix<type_>::~Matrix(){
			if (mPtr)
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

			for (int i = 0; i < mRows; i++){
				std::cout << "\t";
				for (int j = 0; j < mCols; j++){
					std::cout << mPtr[i*mCols + j] << "  ";;
				}
				if (i < mRows - 1)
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

			for (int i = 0; i < mRows; i++){
				ss << "\t";
				for (int j = 0; j < mCols; j++){
					ss << mPtr[i*mCols + j] << "  ";;
				}
				if (i < mRows - 1)
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
			if (this != &_mat){
				if (mRows != _mat.mRows || mCols != _mat.mCols){
					if (mPtr)
						delete[] mPtr;
					mRows = _mat.mRows;
					mCols = _mat.mCols;

					mPtr = new type_[mRows*mCols];
				}
				for (int i = 0; i < mCols*mRows; i++){
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

			for (int i = 0; i < mRows; i++){
				for (int j = 0; j < mCols; j++){
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

			for (int i = 0; i < mRows; i++){
				for (int j = 0; j < mCols; j++){
					mat(i, j) = (*this)(i, j) - _mat(i, j);
				}
			}

			return mat;
		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		Matrix<type_> Matrix<type_>::operator* (const Matrix<type_>& _mat) const{
			assert(mCols == _mat.mRows);

			Matrix<type_> mat(mRows, _mat.mCols);

			for (int i = 0; i < mat.mRows; i++){
				for (int j = 0; j < mat.mCols; j++){
					mat(i, j) = 0;
					for (int k = 0; k < mCols; k++){
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

			for (int i = 0; i < mRows; i++){
				for (int j = 0; j < mCols; j++){
					mat(i, j) = (*this)(i, j) * _scalar;
				}
			}

			return mat;
		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		Matrix<type_> Matrix<type_>::operator^(const double _exp) const{
			Matrix<type_> mat(*this);

			if (_exp < 0){
				mat = mat^-_exp;
				mat = mat.inverse();
			}
			else {
				for (int i = 0; i < mRows; i++){
					for (int j = 0; j < mCols; j++){
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
		Matrix<type_> Matrix<type_>::transpose() {
			Matrix<type_> mat(mCols, mRows);

			for (int i = 0; i < mRows; i++){
				for (int j = 0; j < mCols; j++){
					mat(j, i) = (*this)(i, j);
				}
			}

			return mat;
		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		type_ Matrix<type_>::determinant() {
			if (mCols == mRows){
				Matrix<type_> L(mRows, mCols), U(mRows, mCols);

				if (decompositionLU(L, U)){
					type_ det = U[0];
					for (int i = 1; i < mRows; i++){
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

			for (int i = 0; i < size; i++){
				norm += mPtr[i] * mPtr[i];
			}

			return sqrt(norm);
		}

		//------------------------------------------------------------------------------
		template<typename type_>
		bool Matrix<type_>::decompositionLU(Matrix& _L, Matrix& _U){
			if (_L.mCols != _U.mCols || _L.mCols != mCols ||
				_L.mRows != _U.mRows || _L.mRows != mRows){
				return false;	// Bad matrix sizes
			}

			_U = Matrix<type_>(mPtr, mRows, mCols);

			for (int i = 0; i < mRows; i++){
				_L[i*mCols + i] = 1.0;	// Set de diagonals of L. Eye matrix
				for (int k = i + 1; k < mRows; k++){
					_L[k*mCols + i] = _U[k*mCols + i] / _U[i*mCols + i];
					for (int j = 0; j < mCols; j++){
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
			for (int i = 1; i <= mRows; i++){
				t += i;
			}
			if (mRows < mCols)
				t += (mRows - mCols) * mCols;

			int dim = mRows > mCols ? mRows : mCols;
			_R = *this;
			_Q = createEye<type_>(dim);

			// Creating Givens Rotation matrix
			for (int j = 0; j < mCols; j++){
				for (int i = mRows - 1; i > j; i--){
					double theta = atan(-_R[i*dim + j] / _R[(i - 1)*dim + j]);
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
			if (mCols != mRows)
				assert(false);


			Matrix<type_> matInv = createEye<type_>(mRows), mat(*this);

			// Inferior triangle elimination.
			for (int i = 0; i < mRows; i++){
				for (int k = i + 1; k < mRows; k++){
					double factor = mat[k*mCols + i] / mat[i*mCols + i];
					for (int j = 0; j < mCols; j++){
						mat[k*mCols + j] = mat[k*mCols + j] - mat[i*mCols + j] * factor;
						matInv[k*mCols + j] = matInv[k*mCols + j] - matInv[i*mCols + j] * factor;
					}
				}
			}

			// Superior triangle elimination.
			for (int i = mRows - 1; i > 0; i--){
				for (int k = i - 1; k >= 0; k--){
					double factor = mat[k*mCols + i] / mat[i*mCols + i];
					for (int j = mCols - 1; j >= 0; j--){
						mat[k*mCols + j] = (mat[k*mCols + j] - mat[i*mCols + j] * factor);
						matInv[k*mCols + j] = (matInv[k*mCols + j] - matInv[i*mCols + j] * factor);
					}
				}

				for (int j = 0; j < mCols; j++){	// Unitarize the diagonal
					matInv[i*mCols + j] = matInv[i*mCols + j] / mat[i*mCols + i];
				}
			}

			return matInv;
		}
	}	// namespace math
}	// namespace BOViL