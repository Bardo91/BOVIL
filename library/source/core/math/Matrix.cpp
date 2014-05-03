/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Ramón Soria
//		Date:	2014-04-22
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "Matrix.h"

namespace BOViL{
	namespace math{
		//-----------------------------------------------------------------------------
		Matrix<double> createGivenRotation(int _n, int _i, int _j, double _theta){
			Matrix<double>  mat = createEye<double>(_n);

			mat[_i*_n + _i] = cos(_theta);
			mat[_j*_n + _j] = cos(_theta);
			mat[_i*_n + _j] = sin(_theta);
			mat[_j*_n + _i] = -sin(_theta);

			return mat;
		}

		//-----------------------------------------------------------------------------
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

	}	// namespace math
}	// namespace BOViL