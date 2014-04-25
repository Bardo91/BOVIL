/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Ramón Soria
//		Date:	2014-04-24
//
/////////////////////////////////////////////////////////////////////////////////////////


#include "Geometrics.h"

#include "../math/Matrix.h"

namespace BOViL	{
	namespace geometrics{
		class SubSpace {
			public:
				SubSpace();

			private:
				int mDimension;			//	Dimension of this subspace.
				int mSpaceDimensión;	//	Dimension of the space in which this subspace is refered.
				
				math::Matrix<double> mMatrixEcuations;	// Matrix that contains the coefficients of the ecuations of the subspace.
				math::Matrix<double> mVectorIndepCoef;	// Vector that contains the coefficients of the independent terms ob the ecuations of the subspace.

		};
	}	//	namespace geometrics
}	//	namespace BOViL