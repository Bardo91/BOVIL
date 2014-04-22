/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Ramón Soria
//		Date:	2014-04-22
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "Matrix.inl"

namespace BOViL{
	namespace math{
		template<typename type_>
		Matrix<type_> createEye(int _n){
			Matrix<type_> mat(_n, _n);

			for (int i = 0; i < _n; i++){
				mat[i * _n + i] = 1;
			}

			return mat;
		}

		//-----------------------------------------------------------------------------
		template<typename type_>
		Matrix<type_> createGivenRotation(int _n, int _i, int _j, double _theta){
			Matrix<type_>  mat = createEye<type_>(_n);

			mat[_i*_n + _i] = cos(_theta);
			mat[_j*_n + _j] = cos(_theta);
			mat[_i*_n + _j] = sin(_theta);
			mat[_j*_n + _i] = -sin(_theta);

			return mat;
		}
	}	// namespace math
}	// namespace BOViL