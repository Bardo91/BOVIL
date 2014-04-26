/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Ramón Soria
//		Date:	2014-04-25
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef _BOVIL_CORE_MATH_GEOMETRICS_SUBSPACE_H_
#define _BOVIL_CORE_MATH_GEOMETRICS_SUBSPACE_H_

#include "../../math/Matrix.h"

namespace BOViL	{
	namespace math {
		template <int spaceSize_, int subspaceSize_>
		class LinearSubspace {
		public:		// Constructors
			LinearSubspace();
			LinearSubspace(Matrix<double> &_matrixEcuations, Matrix<double> &_vectorCoef);

		public:		// Functions
			int getDimensionSpace();				// Get the dimension of the subspace
			int getDimensionSubspace();	// Get the dimension of the container of the subspace

			int checkSubspace();

		protected:	// Private Members
			int mSubspaceSize = subspaceSize_;			//	Dimension of this subspace.
			int mSpaceSize = spaceSize_ ;	//	Dimension of the space in which this subspace is refered.

			Matrix<double> mMatrixEcuations;	// Matrix that contains the coefficients of the ecuations of the subspace.
			Matrix<double> mVectorIndepCoef;	// Vector that contains the coefficients of the independent terms ob the ecuations of the subspace.

		};
		
	}	//	namespace math
}	//	namespace BOViL


#endif	//	_BOVIL_CORE_MATH_GEOMETRICS_SUBSPACE_H_