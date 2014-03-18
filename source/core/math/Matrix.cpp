/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-03
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "Matrix.h"

namespace BOViL{
	namespace math{
		Matrix<double> createGivenRotation(int _n, int _i, int _j, double _theta){
			Matrix<double>  mat = createEye<double>(_n);

			*mat[_i*_n + _i] = cos(_theta);
			*mat[_j*_n + _j] = cos(_theta);
			*mat[_i*_n + _j] = sin(_theta);
			*mat[_j*_n + _i] = -sin(_theta);
			
			return mat;
		}

	}	// namespace math
}	//namesapce BOViL