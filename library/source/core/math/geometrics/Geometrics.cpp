/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Raón Soria
//		Date:	2014-05-10
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "Geometrics.h"

namespace BOViL{
	namespace math{
		//-------------------------------------------------------------------------------
		math::Matrix<double> createRotationMatrixEuler(double _alpha, double _beta, double _gamma){
			double arrayRx[9] = { 1, 0, 0,
				0, cos(_alpha), -sin(_alpha),
				0, sin(_alpha), cos(_alpha) };
			double arrayRy[9] = { cos(_beta), 0, sin(_beta),
				0, 1, 0,
				-sin(_beta), 0, cos(_beta) };
			double arrayRz[9] = { cos(_gamma), -sin(_gamma), 0,
				sin(_gamma), cos(_gamma), 0,
				0, 0, 1 };

			math::Matrix<double> Rx(arrayRx, 3, 3);

			math::Matrix<double> Ry(arrayRy, 3, 3);

			math::Matrix<double> Rz(arrayRz, 3, 3);

			return (Rx * Ry * Rz); //Euler angles.

		}

		//-------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------

	}
}