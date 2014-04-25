/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Ramón Soria
//		Date:	2014-04-25
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef _BOVIL_CORE_MATH_GEOMETRICS_LINEAR_SUBSPACE3D_H_
#define _BOVIL_CORE_MATH_GEOMETRICS_LINEAR_SUBSPACE3D_H_

#include "LinearSubspace.h"

namespace BOViL	{
	namespace math {
		class LinearSubspace3D : public LinearSubspace {
		public:		// Constructors
			//LinearSubspace3D();
			LinearSubspace3D(Matrix<double> &_matrixEcuations, Matrix<double> &_vectorCoef);

		public:		// Functions
			bool distanceToSubspace(LinearSubspace3D &_subspace, double &_distance, int &_errorCode);

		};

	}	//	namespace math
}	//	namespace BOViL


#endif	//	_BOVIL_CORE_MATH_GEOMETRICS_LINEAR_SUBSPACE3D_H_