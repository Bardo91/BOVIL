/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Ramón Soria
//		Date:	2014-04-25
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "LinearSubspace3D.h"

#include <cassert>


namespace BOViL	{
	namespace math {
		//-------------------------------------------------------------------------------------
		LinearSubspace3D::LinearSubspace3D(Matrix<double> &_matrixEcuations, Matrix<double> &_vectorCoef) {
			assert(_matrixEcuations.getHeight() == 3);

			LinearSubspace(_matrixEcuations, _vectorCoef);

		}

		//-------------------------------------------------------------------------------------
		bool LinearSubspace3D::distanceToSubspace(LinearSubspace3D &_subspace, double &_distance, int &_errorCode){


		}

		//-------------------------------------------------------------------------------------


		//-------------------------------------------------------------------------------------

	}	//	namespace math
}	//	namespace BOViL
