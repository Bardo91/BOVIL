/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Raón Soria
//		Date:	2014-03-05
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
			int mRows, mCols;
			type_* mPtr;

		};
		//-----------------------------------------------------------------------------
		//---------------- Other functions --------------------------------------------
		template<typename type_>
		Matrix<type_> createEye(int _n);

		template<typename type_>
		Matrix<type_> createGivenRotation(int _n, int _i, int _j, double _theta);

	}	// namespace math
}	// namespace BOViL


#endif	// _BOVIL_CORE_MATH_MATRIX_H_
